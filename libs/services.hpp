#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <iostream>
#include <cstdlib>

#define SM_ASSERT(cond, msg) \
    do { \
        if (!(cond)) { \
            std::cerr << "Assertion failed: " << msg << std::endl; \
            std::abort(); \
        } \
    } while (0)

namespace allocationService {
struct BumpAllocator
{
    size_t capacity;
    size_t used;
    char* memory;
};

#define SM_ERROR(fmt, ...) \
    fprintf(stderr, fmt "\n", __VA_ARGS__)
BumpAllocator make_bump_allocator(size_t size)
{
    BumpAllocator ba = {};

    ba.memory = (char*)malloc(size);
    if(ba.memory)
    {
        ba.capacity = size;
        memset(ba.memory, 0,size);
    }
    else
    {
        SM_ASSERT(false, "Failed to allocate Memory");
    }

    return ba;
}

char* bump_alloc(BumpAllocator* bumpAllocator, size_t size)
{
    char* result = nullptr;

    size_t allignedSize = (size + 7) & ~ 7;
    if(bumpAllocator->used + allignedSize <= bumpAllocator->capacity)
    {
        result = bumpAllocator->memory + bumpAllocator->used;
        bumpAllocator->used += allignedSize;
    }
    else
    {
        SM_ASSERT(false,"BumpAllocator is full");
    }

    return result;
}

long long get_timestamp(char* file)
{
    struct stat file_stat = {};
    stat(file, &file_stat);
    return file_stat.st_mtime;
}

bool file_exists(char* filePath)
{
    SM_ASSERT(filePath, "No filePath supplied!");

    auto file = fopen(filePath, "rb");
    if(!file)
    {
        return false;
    }
    fclose(file);

    return true;
}

long get_file_size(char* filePath)
{
    SM_ASSERT(filePath, "No filePath supplied!");

    long fileSize = 0;
    auto file = fopen(filePath, "rb");
    if(!file)
    {
        SM_ERROR("Failed opening File: %s", filePath);
        return 0;
    }

    fseek(file,0,SEEK_END);
    fileSize = ftell(file);
    fseek(file,0,SEEK_SET);
    fclose(file);
    return fileSize;
}

char* read_file(char* filePath, int* fileSize, char* buffer)
{
    SM_ASSERT(filePath,"No filePath supplied!");
    SM_ASSERT(fileSize, "No fileSize supplied!");
    SM_ASSERT(buffer, "No buffer supplied!");

    *fileSize = 0;
    auto file = fopen(filePath, "rb");
    if(!file)
    {
        SM_ERROR("Failed opening file: %s", filePath);
        return nullptr;
    }

    fseek(file,0, SEEK_END);
    *fileSize = ftell(file);
    fseek(file,0, SEEK_SET);

    memset(buffer, 0, *fileSize + 1);
    fread(buffer,sizeof(char), *fileSize,file);
    fclose(file);

    return buffer;
}

char* read_file(char* filePath, int* fileSize,BumpAllocator* bumpAllocator)
{
    char* file = nullptr;
    long fileSize2 = get_file_size(filePath);

    if(fileSize2)
    {
        char* buffer = bump_alloc(bumpAllocator, fileSize2 + 1);

        read_file(filePath,fileSize,buffer);
    }

    return file;
}

void write_file(char* filePath,char* buffer, int size)
{
    SM_ASSERT(filePath, "No filePath supplied!");
    SM_ASSERT(buffer, "No buffer supplied!");
    auto file = fopen(filePath, "wb");
    if(!file)
    {
        SM_ERROR("Failed opening File: %s", filePath);
        return;
    }

    fwrite(buffer,sizeof(char),size,file);
    fclose(file);
}

bool copy_file(char* fileName, char* outputName, char* buffer)
{
    int fileSize = 0;
    char* data = read_file(fileName, &fileSize, buffer);

    auto outputFile = fopen(outputName, "wb");
    if(!outputFile)
    {
        SM_ERROR("Failed opening File: %s", outputName);
        return false;
    }

    int result = fwrite(data,sizeof(char),fileSize,outputFile);
    if (!result)
    {
        SM_ERROR("Failed opening File: %s",outputName);
        return false;
    }

    fclose(outputFile);

    return true;
}

bool copy_file(char* fileName, char* outputName, BumpAllocator* bumpAllocator)
{
    char* file = nullptr;
    long fileSize2 = get_file_size(fileName);

    if(fileSize2)
    {
        char* buffer = bump_alloc(bumpAllocator, fileSize2 + 1);

        return copy_file(fileName,outputName,buffer);
    }

    return file;
}

}