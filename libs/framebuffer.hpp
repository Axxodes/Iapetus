#pragma once
#include <cstdlib>
#include <cstring>
#include <iostream>

struct FrameBuffer
{
    size_t capacity;
    char* memory;
};

FrameBuffer fa {};

FrameBuffer createFrameBuffer(size_t size)
{
    fa.memory = (char*)std::malloc(size);
    if (fa.memory)
    {
        fa.capacity = size;
        memset(fa.memory, 0, size);
    }
    else
    {
        std::cout << "Error, framebuffer failed to allocate.";
    }

    return fa;
}