#include <windows.h>
#include <iostream>

DWORD g_maxReadSize = 4096 * 4096;
DWORD g_maxWriteSize = 4096 * 4096;
wchar_t* g_fileBuffer = nullptr;

OVERLAPPED readOV = { 0, };
OVERLAPPED writeOV = { 0, };
LARGE_INTEGER g_loadFileSize;
LARGE_INTEGER g_read = { 0, };
LARGE_INTEGER g_write = { 0, };
DWORD readCounter = 0;
DWORD writeCounter = 0;

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
                //isPending = false;
            }
            isPending = false;
            std::cout << readCounter-- << std::endl;
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
            std::cout << writeCounter-- << std::endl;
        }
    }
    return writeBytes;
}

LARGE_INTEGER LoadAsync(std::wstring file) {

    HANDLE readFile = CreateFile(file.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL);   // overlapped -> async

    if (readFile != INVALID_HANDLE_VALUE) {
        ::GetFileSizeEx(readFile, &g_loadFileSize);
        if (g_maxReadSize > g_loadFileSize.QuadPart) {                                                      // 한번에 읽을 수 있는 크기면 분할할 필요 없음
            g_maxReadSize = g_loadFileSize.QuadPart;
        }

        g_fileBuffer = new wchar_t[g_loadFileSize.QuadPart];
        readCounter = g_loadFileSize.LowPart / g_maxReadSize;

        DWORD offset = g_maxReadSize;
        while (1) {
            DWORD readBytes = ReadSplit(readFile, offset);

            // 분할 로드 && 파일 사이즈 == 이미 읽은 바이트 + 마지막 분할 바이트 -> 로드 완료
            if (readBytes < g_maxReadSize && g_loadFileSize.QuadPart == g_read.QuadPart + readBytes) {
                break;
            }
            g_read.QuadPart += readBytes;                                                                   // 읽은 바이트 누적
            readOV.Offset = g_read.LowPart;
            readOV.OffsetHigh = g_read.HighPart;

            // 누적바이트 + 읽기 버퍼 사이즈가 파일 사이즈보다 크면 다음 분할 로드에서 파일 로드 완료 가능 -> 다음 오프셋은 남은 파일 바이트만큼만 로드하면 됨
            if ((readOV.Offset + g_maxReadSize) > g_loadFileSize.QuadPart) {
                offset = (g_loadFileSize.QuadPart - readOV.Offset);
            }
        }
        CloseHandle(readFile);
    }
    return g_loadFileSize;
}

LARGE_INTEGER CopyAsync(std::wstring file, LARGE_INTEGER fileSize) {

    HANDLE writeFile = CreateFile(file.c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL);

    if (writeFile != INVALID_HANDLE_VALUE) {
        if (g_maxWriteSize > fileSize.QuadPart) {                                                      // 한번에 읽을 수 있는 크기면 분할할 필요 없음
            g_maxWriteSize = fileSize.QuadPart;
        }
        writeCounter = fileSize.LowPart / g_maxWriteSize;
        DWORD offset = g_maxWriteSize;
        while (1) {
            DWORD writeBytes = WriteSplit(writeFile, offset);
            if (writeBytes < g_maxWriteSize && fileSize.QuadPart == g_write.QuadPart + writeBytes) {
                break;
            }
            g_write.QuadPart += writeBytes;
            writeOV.Offset = g_write.LowPart;
            writeOV.OffsetHigh = g_write.HighPart;

            if ((writeOV.Offset + g_maxWriteSize) > fileSize.QuadPart) {
                offset = (fileSize.QuadPart - writeOV.Offset);
            }
        }
        CloseHandle(writeFile);

    }
    return fileSize;
}



int main()
{
    std::wstring read = L"test.txt";
    std::wstring write = L"Copy.txt";

    LARGE_INTEGER fileSize = LoadAsync(read);
    CopyAsync(write, fileSize);

    std::cout << "Hello World!\n";
}
