#pragma once
#include <windows.h>

struct FileBuffer
{
    size_t capacity;
    size_t used;
    char* memory;
};

FileBuffer fileBuffer {};

#define RESET_FILEBUFFER() do { \
std::free(fileBuffer.memory); \
fileBuffer.capacity = 0; \
fileBuffer.used = 0;} \
while (false) 

bool allocateFileBuffer(size_t size)
{
    // round UP for the input

    RESET_FILEBUFFER();

    fileBuffer.memory = (char*)std::malloc(size);
    if(!fileBuffer.memory)
    {
        OUTPUT_ERROR("FileBuffer failed to allocated, trying again...");
        fileBuffer.memory = (char*)std::malloc(size);
        if(!fileBuffer.memory)
        {
            OUTPUT_ERROR("FileBuffer failed to allocate twice... aborting.");
            return false;
        }
    }
    fileBuffer.capacity = size;
    memset(fileBuffer.memory,0, size);
    return true;
}

bool openProject(const wchar_t* name)
{
    // you can create a wide char by putting L infront of the first quotation mark

    if (std::wcspbrk(name, L"\\/:"))
    {
        OUTPUT_ERROR("Project name must not contain path separators.");
        return false;
    }

    auto dirPath = std::wstring(L"projects\\") + name;

    if (!CreateDirectoryW(dirPath.c_str(),NULL))
    {
        DWORD error = GetLastError();
        if (error != ERROR_ALREADY_EXISTS)
        {
            OUTPUT_ERROR("Tried to create directory, failed for reason: " << error);
            return false;
        }
    }

    auto fileName = std::wstring(dirPath.c_str()) + L"\\" + name + L".iap";

    HANDLE file = CreateFileW(fileName.c_str(),GENERIC_READ | GENERIC_WRITE,FILE_SHARE_READ,NULL,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
    if (file == INVALID_HANDLE_VALUE)
    {
        DWORD error = GetLastError();
        OUTPUT_ERROR("Tried to create .iap file in project directory, returning error: " << error);
        return false;
    }

    LARGE_INTEGER filesize {};
    

    if(GetFileSizeEx(file,&filesize) == 0)
    {
        OUTPUT_ERROR("Filesize acquired below 0, trying again...");
        if(GetFileSizeEx(file,&filesize) == 0)
        {
            OUTPUT_ERROR("Filesize acquired below 0, aborting");
            return false;
        }
    }

    DWORD bytesRead = 0;

    if(!allocateFileBuffer(filesize.QuadPart))
    {
        return false;
    }

    if(!ReadFile(file,fileBuffer.memory,static_cast<DWORD>(fileBuffer.capacity),&bytesRead,nullptr))
    {
        DWORD error = GetLastError();
        OUTPUT_ERROR("Tried to fill FileBuffer with file data, (hint: it failed) returning error: " << error);

        CloseHandle(file);
        std::free(fileBuffer.memory);
        fileBuffer.capacity = 0;
        fileBuffer.used = 0;
        return false;
    }

    fileBuffer.used = bytesRead;

    CloseHandle(file);
    return true;
}

bool loadFontIntoFileBuffer(const wchar_t* name)
{
    auto filePath = std::wstring(L"libs\\Hyperion\\Fonts\\") + name;
    HANDLE file = CreateFileW(filePath.c_str(),GENERIC_READ | GENERIC_WRITE,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);

    if (file == INVALID_HANDLE_VALUE)
    {
        DWORD error = GetLastError();
        // do shit
        OUTPUT_ERROR("Failed to initialise HANDLE object while loading font, (hint: " << error << ") aborting..."); 
        return false;
    }

    LARGE_INTEGER filesize {};
    
    if(GetFileSizeEx(file,&filesize) == 0)
    {
        const DWORD error = GetLastError();
        OUTPUT_ERROR("Failed to fetch filesize, (hint: " << error << ") trying again..."); 
        if(GetFileSizeEx(file,&filesize) == 0)
        {
            const DWORD error2 = GetLastError();
            OUTPUT_ERROR("Failed to fetch filesize, (hint: " << error2 <<") trying again..."); 
            return false;
        }
    }

    if(!allocateFileBuffer(filesize.QuadPart))
    {
        return false;
    }

    DWORD bytesRead = 0;

    if(!ReadFile(file,fileBuffer.memory,static_cast<DWORD>(fileBuffer.capacity),&bytesRead,nullptr))
    {
        DWORD error = GetLastError();
        OUTPUT_ERROR("Tried to fill FileBuffer with file data, (hint: it failed) returning error: " << error);

        CloseHandle(file);
        std::free(fileBuffer.memory);
        fileBuffer.capacity = 0;
        fileBuffer.used = 0;
        return false;
    }

    fileBuffer.used = bytesRead;

    CloseHandle(file);
    return true;
}