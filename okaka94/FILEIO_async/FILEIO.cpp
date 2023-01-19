#include <windows.h>
#include <iostream>

wchar_t* g_fileBuffer = 0;

DWORD LoadAsync(std::wstring file) {
    HANDLE readFile = CreateFile(file.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL);   // overlapped -> async
    OVERLAPPED readOV = { 0, };
    DWORD read = 0;
    LARGE_INTEGER fileSize;
    bool isPending = false;

    if (readFile != INVALID_HANDLE_VALUE) {
        ::GetFileSizeEx(readFile, &fileSize);
        g_fileBuffer = new wchar_t[fileSize.LowPart];
        BOOL ret = ReadFile(readFile, g_fileBuffer, fileSize.QuadPart, &read, &readOV);

        if (ret == FALSE) {
            if (GetLastError() == ERROR_IO_PENDING) {                                           // IO operation is in progress
                isPending = true;
            }
        }
        if (ret == TRUE) {

        }
        while (isPending) {
            ret = ::GetOverlappedResult(readFile, &readOV, &read, FALSE);
            if (ret == TRUE) {
                isPending = false;
            }
            std::cout << readOV.Internal << " ";
        }

        CloseHandle(readFile);
    }
    return read;
}

DWORD CopyAsync(std::wstring file, DWORD fileSize) {
    HANDLE writeFile = CreateFile(file.c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL);

    OVERLAPPED writeOV = { 0, };
    DWORD write = 0;
    bool isPending = false;
    
    if (writeFile != INVALID_HANDLE_VALUE) {
        BOOL ret = ::WriteFile(writeFile, g_fileBuffer, fileSize, &write, &writeOV);
        if (ret == FALSE) {
            if (GetLastError() == ERROR_IO_PENDING) {
                isPending = true;
            }
        }
        if (ret == TRUE) {

        }
        while (isPending) {
            ret = ::GetOverlappedResult(WriteFile, &writeOV, &write, FALSE);
            if (ret == TRUE) {
                isPending = false;
            }
            std::cout << writeOV.Internal << " ";
        }
        CloseHandle(writeFile);
    }
    return write;
}



int main()
{
    std::wstring read = L"Text.txt";
    std::wstring write = L"Copy.txt";

    DWORD fileSize = LoadAsync(read);
    CopyAsync(write, fileSize);

    std::cout << "Hello World!\n";
}