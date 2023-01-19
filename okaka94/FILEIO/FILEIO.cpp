#include <windows.h>
#include <iostream>

wchar_t* g_fileBuffer = 0;

DWORD Load(std::wstring file) {
    HANDLE readFile = CreateFile(file.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    DWORD read = 0;
    LARGE_INTEGER fileSize;

    if (readFile != INVALID_HANDLE_VALUE) {
        ::GetFileSizeEx(readFile, &fileSize);
        g_fileBuffer = new wchar_t[fileSize.LowPart];
        BOOL ret = ReadFile(readFile, g_fileBuffer, fileSize.QuadPart, &read, NULL);

        if (ret == TRUE) {

        }
        CloseHandle(readFile);
    }
    return read;
}

DWORD Copy(std::wstring file, DWORD fileSize) {
    HANDLE writeFile = CreateFile(file.c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    DWORD write = 0;
    
    if (writeFile != INVALID_HANDLE_VALUE) {
        BOOL ret = ::WriteFile(writeFile, g_fileBuffer, fileSize, &write, NULL);
        if (ret == TRUE) {

        }
        CloseHandle(writeFile);
    }
    return write;
}


int main()
{
    std::wstring read = L"Text.txt";
    std::wstring write = L"Copy.txt";

    DWORD fileSize = Load(read);
    Copy(write, fileSize);

    std::cout << "Hello World!\n";
}
