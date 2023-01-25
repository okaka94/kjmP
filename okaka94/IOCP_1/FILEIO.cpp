#include <windows.h>
#include <iostream>
#include <process.h>

HANDLE g_IOCP;
HANDLE g_eventFinish;
HANDLE readFile;
HANDLE writeFile;

DWORD g_maxReadSize = 4096 * 4096;
DWORD g_maxWriteSize = 4096 * 4096;
wchar_t* g_fileBuffer = nullptr;

OVERLAPPED readOV = { 0, };
OVERLAPPED writeOV = { 0, };
LARGE_INTEGER g_loadFileSize;
LARGE_INTEGER g_read = { 0, };
LARGE_INTEGER g_write = { 0, };

unsigned WINAPI workProc(LPVOID param) {

    DWORD transferredBytes;
    ULONG_PTR keyValue;
    OVERLAPPED* OV;

    DWORD readOffset = g_maxReadSize;
    //DWORD writeOffset = g_maxWriteSize; // maxReadSize 인 이유?

    while (1) {
        DWORD event = WaitForSingleObject(g_eventFinish, 0);
        if (event == WAIT_OBJECT_0) {
            break;
        }
        BOOL ret = ::GetQueuedCompletionStatus(g_IOCP, &transferredBytes, &keyValue, &OV, INFINITE);
        if (ret == TRUE) {          // 비동기 IO 작업 완료
            if (keyValue == 1) {    // 읽기 완료
                g_read.QuadPart += transferredBytes;
                readOV.Offset = g_read.LowPart;
                readOV.OffsetHigh = g_read.HighPart;

                DWORD writtenBytes = 0;
                wchar_t* offsetData = &g_fileBuffer[g_write.QuadPart];
                BOOL ret = ::WriteFile(writeFile, offsetData, transferredBytes, &writtenBytes, &writeOV);
            }
            if (keyValue == 2) {    // 쓰기 완료
                if (readOV.Offset == g_loadFileSize.QuadPart) {
                    ::SetEvent(g_eventFinish);
                }
                else {
                    g_write.QuadPart += transferredBytes;
                    writeOV.Offset = g_write.LowPart;
                    writeOV.OffsetHigh = g_write.HighPart;

                    wchar_t* offsetData = &g_fileBuffer[g_read.QuadPart];

                    DWORD read;
                    BOOL ret = ::ReadFile(readFile, offsetData, readOffset, &read, &readOV);
                }
            }
        }
        else {
            DWORD error = GetLastError();
            if (error == ERROR_HANDLE_EOF) {
                break;
            }
            else {
                //error
            }
        }
    }
    return 0;
}



void main()
{
    g_eventFinish = ::CreateEvent(NULL, TRUE, FALSE, NULL);                     // Manual Reset : TRUE , Initial State : FALSE
    
    
    std::wstring readFileName = L"test.exe";
    std::wstring writeFileName = L"Copy.exe";

    readFile = CreateFile(readFileName.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL);
    if (readFile == INVALID_HANDLE_VALUE) {
        return;
    }
    writeFile = CreateFile(writeFileName.c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL);
    if (writeFile == INVALID_HANDLE_VALUE) {
        return;
    }

    g_IOCP = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0);   // ExistingCompletionPort 매개 변수가 NULL이면 반환 값은 새 핸들
    ::CreateIoCompletionPort(readFile, g_IOCP, 1, 0);
    ::CreateIoCompletionPort(writeFile, g_IOCP, 2, 0);

    ::GetFileSizeEx(readFile, &g_loadFileSize);
    g_fileBuffer = new wchar_t[g_loadFileSize.QuadPart];

    unsigned int workID;
    unsigned long workThread = _beginthreadex(NULL, 0, workProc, (void*)readFileName.c_str(), 0, &workID);
    
    g_read.QuadPart += 0;
    readOV.Offset = g_read.LowPart;
    readOV.OffsetHigh = g_read.HighPart;

    DWORD readBytes;
    DWORD ret = ::ReadFile(readFile, g_fileBuffer, g_maxReadSize, &readBytes, &readOV);

    ret = GetLastError();
    if (ret == TRUE) {
        std::cout << "O";
    }

    WaitForSingleObject((HANDLE)workThread, INFINITE);
    CloseHandle((HANDLE)workThread);

    CloseHandle(readFile);
    CloseHandle(writeFile);

    delete[] g_fileBuffer;

}


