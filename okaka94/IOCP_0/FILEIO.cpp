#include <windows.h>
#include <iostream>
#include <process.h>

HANDLE g_eventWriteStart;
HANDLE g_eventMain;

DWORD g_maxReadSize = 4096 * 4096;
DWORD g_maxWriteSize = 4096 * 4096;
wchar_t* g_fileBuffer = nullptr;

OVERLAPPED readOV = { 0, };
OVERLAPPED writeOV = { 0, };
LARGE_INTEGER g_loadFileSize;
LARGE_INTEGER g_read = { 0, };
LARGE_INTEGER g_write = { 0, };

DWORD ReadSplit(HANDLE file, DWORD offset) {
    DWORD readBytes = 0;
    wchar_t* offsetData = &g_fileBuffer[g_read.QuadPart];
    BOOL ret = ::ReadFile(file, offsetData, offset, &readBytes, &readOV);
    bool isPending = false;
    if (ret == FALSE) {
        DWORD error = GetLastError();
        if (error == ERROR_IO_PENDING) {
            isPending = true;
        }
    }
    if (ret == TRUE) {                                                                              // 비동기적으로 완료되는 경우에도 FALSE 리턴됨
        std::cout << "Read Complete\n";
    }
    while (isPending) {
        ret = ::GetOverlappedResult(file, &readOV, &readBytes, FALSE);
        if (ret == TRUE) {
            if (readBytes != g_maxReadSize) {

            }
            isPending = false;
        }
    }
    return readBytes;
}

DWORD WriteSplit(HANDLE file, DWORD offset) {

    DWORD writeBytes = 0;
    wchar_t* offsetData = &g_fileBuffer[g_write.QuadPart];
    BOOL ret = ::WriteFile(file, offsetData, offset, &writeBytes, &writeOV);

    bool isPending = false;
    if (ret == FALSE) {
        DWORD error = GetLastError();
        if (error == ERROR_IO_PENDING) {
            isPending = true;
        }
    }
    if (ret == TRUE) {
        std::cout << "Write Complete\n";
    }

    while (isPending) {
        ret = ::GetOverlappedResult(file, &writeOV, &writeBytes, FALSE);
        if (ret == TRUE) {
            if (writeBytes != g_maxWriteSize) {

            }
            isPending = false;
        }
    }
    return writeBytes;
}

unsigned WINAPI readProc(LPVOID param) {

    std::wstring file = (WCHAR*)param;
    HANDLE readFile = CreateFile(file.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL);   // overlapped -> async

    if (readFile == INVALID_HANDLE_VALUE) {
        return false;
    }

    ::GetFileSizeEx(readFile, &g_loadFileSize);
    if (g_maxReadSize > g_loadFileSize.QuadPart) {                                                      // 한번에 읽을 수 있는 크기면 분할할 필요 없음
        g_maxReadSize = g_loadFileSize.QuadPart;
    }

    g_fileBuffer = new wchar_t[g_loadFileSize.QuadPart];
    
    DWORD offset = g_maxReadSize;
    bool isCompleted = false;
    while (isCompleted == false) {

        DWORD readBytes = ReadSplit(readFile, offset);

        ::SetEvent(g_eventWriteStart);                                                                  // read 한 후에 write 시작하도록 set event

        // 분할 로드 && 파일 사이즈 == 이미 읽은 바이트 + 마지막 분할 바이트 -> 로드 완료
        if (readBytes < g_maxReadSize && g_loadFileSize.QuadPart == g_read.QuadPart + readBytes) {
            g_read.QuadPart += readBytes;                                                                   // 읽은 바이트 누적
            isCompleted = true;
        }
        else {
            g_read.QuadPart += readBytes;                                                                   // 읽은 바이트 누적
            readOV.Offset = g_read.LowPart;
            readOV.OffsetHigh = g_read.HighPart;

            // 누적바이트 + 읽기 버퍼 사이즈가 파일 사이즈보다 크면 다음 분할 로드에서 파일 로드 완료 가능 -> 다음 오프셋은 남은 파일 바이트만큼만 로드하면 됨
            if ((readOV.Offset + g_maxReadSize) > g_loadFileSize.QuadPart) {
                offset = (g_loadFileSize.QuadPart - readOV.Offset);
            }
        }
        
    }
     CloseHandle(readFile);
    
    return 0;
}

unsigned WINAPI writeProc(LPVOID param) {

    std::wstring file = (WCHAR*)param;
    HANDLE writeFile = CreateFile(file.c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL);

    if (writeFile == INVALID_HANDLE_VALUE) {
        return false;
    }
          
    if (g_maxWriteSize > g_loadFileSize.QuadPart) {                                                      // 한번에 읽을 수 있는 크기면 분할할 필요 없음
        g_maxWriteSize = g_loadFileSize.QuadPart;
    }
    
    DWORD offset = g_maxWriteSize;
    bool isCompleted = false;

    while (isCompleted == false) {

        WaitForSingleObject(g_eventWriteStart, INFINITE);

        DWORD writeBytes = WriteSplit(writeFile, offset);
        if (writeBytes < g_maxWriteSize && g_loadFileSize.QuadPart == g_write.QuadPart + writeBytes) {
            isCompleted = true;
            break;
        }

        g_write.QuadPart += writeBytes;
        writeOV.Offset = g_write.LowPart;
        writeOV.OffsetHigh = g_write.HighPart;

        if ((writeOV.Offset + g_maxWriteSize) > g_loadFileSize.QuadPart) {
            offset = (g_loadFileSize.QuadPart - writeOV.Offset);
        }
        ::SetEvent(g_eventMain);
    }
    CloseHandle(writeFile);

    
    return 0;
}



int main()
{
    g_eventWriteStart = ::CreateEvent(NULL, TRUE, FALSE, NULL);                     // Manual Reset : TRUE , Initial State : FALSE
    g_eventMain = ::CreateEvent(NULL, TRUE, FALSE, NULL);

    unsigned int readID, writeID;
    std::wstring readFile = L"LOL.exe";
    std::wstring writeFile = L"Copy.exe";

    unsigned long readThread = _beginthreadex(NULL, 0, readProc, (void*)readFile.c_str(), 0, &readID);
    unsigned long writeThread = _beginthreadex(NULL, 0, writeProc, (void*)writeFile.c_str(), 0, &writeID);

    while (1) {
        WaitForSingleObject(g_eventMain, INFINITE);
        float currentLoad = (float)g_read.QuadPart / (float)g_loadFileSize.QuadPart;
        std::cout << currentLoad * 100.0f << "\n";
        if (g_read.QuadPart == g_loadFileSize.QuadPart) {
            break;
        }
    }

    WaitForSingleObject((HANDLE)readThread, INFINITE);
    WaitForSingleObject((HANDLE)writeThread, INFINITE);
    CloseHandle((HANDLE)readThread);
    CloseHandle((HANDLE)writeThread);

}


