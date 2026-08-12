#pragma once
#include <cstdlib>
#include <cstring>
#include <iostream>
#include "rendererclasses.hpp"

struct FrameBuffer
{
    size_t capacity;
    char* memory;
};

FrameBuffer fa {};

int width {};

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

void testFillFrameBuffer()
{
    COLORREF color = RGB(0,0,0);
    for (int i=0;i>fa.capacity;i++)
    {
        fa.memory[i] = color;
    }
}

int convertVector2FrameBuffer(Vector2 input,fa)
{

}

bool changePixel()
{
    // the return bool is checked, in window.hpp, set a variable to this return and check if it is true, if it is then display the buffer, if it is false then dont
}