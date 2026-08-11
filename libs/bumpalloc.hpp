#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <iostream>
#include <cstdlib>
#include <cstdio>


#define SM_ASSERT(cond, msg) \
    do { \
        if (!(cond)) { \
            std::cerr << "Assertion failed: " << msg << std::endl; \
            std::abort(); \
        } \
    } while (0)


namespace allocationService
{

struct BumpAllocator
{
    size_t capacity;
    size_t used;
    char* memory;
};


BumpAllocator ba {};


#define SM_ERROR(fmt, ...) \
    fprintf(stderr, fmt "\n", __VA_ARGS__)


BumpAllocator make_bump_allocator(size_t size)
{
    ba.memory = (char*)malloc(size);

    if (ba.memory)
    {
        ba.capacity = size;
        ba.used = 0;
        memset(ba.memory, 0, size);
    }
    else
    {
        SM_ASSERT(false, "Failed to allocate Memory");
    }

    return ba;
}


char* bump_alloc(BumpAllocator* bumpAllocator, size_t size)
{
    SM_ASSERT(bumpAllocator, "No BumpAllocator supplied!");

    size_t alignedSize = (size + 7) & ~static_cast<size_t>(7);

    if (bumpAllocator->used + alignedSize <= bumpAllocator->capacity)
    {
        char* result = bumpAllocator->memory + bumpAllocator->used;
        bumpAllocator->used += alignedSize;

        return result;
    }

    SM_ASSERT(false, "BumpAllocator is full");

    return nullptr;
}


long long get_timestamp(const char* file)
{
    SM_ASSERT(file, "No file supplied!");

    struct stat file_stat = {};

    if (stat(file, &file_stat) != 0)
    {
        SM_ERROR("Failed to stat file: %s", file);
        return 0;
    }

    return file_stat.st_mtime;
}


bool file_exists(const char* filePath)
{
    SM_ASSERT(filePath, "No filePath supplied!");

    auto file = fopen(filePath, "rb");

    if (!file)
    {
        return false;
    }

    fclose(file);

    return true;
}


long get_file_size(const char* filePath)
{
    SM_ASSERT(filePath, "No filePath supplied!");

    auto file = fopen(filePath, "rb");

    if (!file)
    {
        SM_ERROR("Failed opening File: %s", filePath);
        return 0;
    }

    if (fseek(file, 0, SEEK_END) != 0)
    {
        fclose(file);
        SM_ERROR("Failed seeking File: %s", filePath);
        return 0;
    }

    long fileSize = ftell(file);

    if (fileSize < 0)
    {
        fclose(file);
        SM_ERROR("Failed getting size of File: %s", filePath);
        return 0;
    }

    fclose(file);

    return fileSize;
}


char* read_file(const char* filePath, int* fileSize, char* buffer)
{
    SM_ASSERT(filePath, "No filePath supplied!");
    SM_ASSERT(fileSize, "No fileSize supplied!");
    SM_ASSERT(buffer, "No buffer supplied!");

    *fileSize = 0;

    auto file = fopen(filePath, "rb");

    if (!file)
    {
        SM_ERROR("Failed opening file: %s", filePath);
        return nullptr;
    }

    if (fseek(file, 0, SEEK_END) != 0)
    {
        fclose(file);
        SM_ERROR("Failed seeking file: %s", filePath);
        return nullptr;
    }

    long size = ftell(file);

    if (size < 0)
    {
        fclose(file);
        SM_ERROR("Failed getting file size: %s", filePath);
        return nullptr;
    }

    if (fseek(file, 0, SEEK_SET) != 0)
    {
        fclose(file);
        SM_ERROR("Failed seeking file: %s", filePath);
        return nullptr;
    }

    *fileSize = static_cast<int>(size);

    size_t bytesRead = fread(buffer, sizeof(char), *fileSize, file);

    fclose(file);

    if (bytesRead != static_cast<size_t>(*fileSize))
    {
        SM_ERROR("Failed reading file: %s", filePath);
        *fileSize = 0;
        return nullptr;
    }

    buffer[*fileSize] = '\0';

    return buffer;
}


char* read_file(const char* filePath, int* fileSize, BumpAllocator* bumpAllocator)
{
    SM_ASSERT(filePath, "No filePath supplied!");
    SM_ASSERT(fileSize, "No fileSize supplied!");
    SM_ASSERT(bumpAllocator, "No BumpAllocator supplied!");

    long fileSize2 = get_file_size(filePath);

    if (fileSize2 <= 0)
    {
        *fileSize = 0;
        return nullptr;
    }

    char* buffer = bump_alloc(
        bumpAllocator,
        static_cast<size_t>(fileSize2) + 1
    );

    return read_file(filePath, fileSize, buffer);
}


void write_file(const char* filePath, const char* buffer, int size)
{
    SM_ASSERT(filePath, "No filePath supplied!");
    SM_ASSERT(buffer, "No buffer supplied!");
    SM_ASSERT(size >= 0, "Invalid file size!");

    auto file = fopen(filePath, "wb");

    if (!file)
    {
        SM_ERROR("Failed opening File: %s", filePath);
        return;
    }

    size_t bytesWritten = fwrite(
        buffer,
        sizeof(char),
        size,
        file
    );

    fclose(file);

    if (bytesWritten != static_cast<size_t>(size))
    {
        SM_ERROR("Failed writing File: %s", filePath);
    }
}


bool copy_file(const char* fileName, const char* outputName, char* buffer)
{
    SM_ASSERT(fileName, "No fileName supplied!");
    SM_ASSERT(outputName, "No outputName supplied!");
    SM_ASSERT(buffer, "No buffer supplied!");

    int fileSize = 0;

    char* data = read_file(fileName, &fileSize, buffer);

    if (!data)
    {
        return false;
    }

    auto outputFile = fopen(outputName, "wb");

    if (!outputFile)
    {
        SM_ERROR("Failed opening File: %s", outputName);
        return false;
    }

    size_t bytesWritten = fwrite(
        data,
        sizeof(char),
        fileSize,
        outputFile
    );

    fclose(outputFile);

    if (bytesWritten != static_cast<size_t>(fileSize))
    {
        SM_ERROR("Failed writing File: %s", outputName);
        return false;
    }

    return true;
}


bool copy_file(
    const char* fileName,
    const char* outputName,
    BumpAllocator* bumpAllocator
)
{
    SM_ASSERT(fileName, "No fileName supplied!");
    SM_ASSERT(outputName, "No outputName supplied!");
    SM_ASSERT(bumpAllocator, "No BumpAllocator supplied!");

    long fileSize = get_file_size(fileName);

    if (fileSize <= 0)
    {
        return false;
    }

    char* buffer = bump_alloc(
        bumpAllocator,
        static_cast<size_t>(fileSize) + 1
    );

    return copy_file(fileName, outputName, buffer);
}


void cleanup()
{
    free(ba.memory);

    ba.memory = nullptr;
    ba.capacity = 0;
    ba.used = 0;
}

}