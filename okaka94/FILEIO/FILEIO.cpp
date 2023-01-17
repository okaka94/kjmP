#include <windows.h>
#include <iostream>

wchar_t* g_fileBuffer = 0;

DWORD Load(std::wstring file) {
    HANDLE readFile = CreateFile(file.c_str(), GENERIC_READ, 0 , NULL , OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL)
}


int main()
{
    std::wstring read = L"Text.iso";
    std::wstring write = L"Copy.zip";

    DWORD fileSize = Load(read);
    Copy(write, fileSize);

    std::cout << "Hello World!\n";
}
