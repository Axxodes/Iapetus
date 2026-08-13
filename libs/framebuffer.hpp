#pragma once
#include <cstdlib>
#include <cstring>
#include <iostream>
#include "rendererclasses.hpp"
#include "propertiesclasses.hpp"
#include <windows.h>

struct FrameBuffer
{
    size_t capacity;
    COLORREF* memory;
};

FrameBuffer fa {};

int width {};

FrameBuffer createFrameBuffer(size_t size, int widthIn)
{
    fa.memory = (COLORREF*)std::malloc(size);
    if (fa.memory)
    {
        fa.capacity = size;
        memset(fa.memory, 0, size);
    }
    else
    {
        std::cout << "Error, framebuffer failed to allocate.";
    }

    width = widthIn;

    return fa;
}

bool reAllocFrameBuffer(size_t size, int widthIn)
{
    if (!fa.memory)
    {
        return false;
    }
    else
    {
        std::free(fa);
        fa.memory = (COLORREF*)std::malloc(size);
        if (fa.memory)
        {
            fa.capacity = size;
            memset(fa.memory, 0, size);
        }
        else
        {
            std::cout << "Error, framebuffer failed to allocate.";
        }

        width = widthIn;

        return true;
    }
}

void testFillFrameBuffer()
{
    COLORREF color = RGB(0,0,0);
    for (int i=0;i>fa.capacity;i++)
    {
        fa.memory[i] = color;
    }
}

int convertVector2FrameBuffer(Vector2 input)
{
    if (width)
    {
        return input.y * width + input.x;
    }
    return 0;
}

bool changePixel(Vector2 position, Color3 colorIn)
{
    // the return bool is checked in window.hpp, set a variable to this return and check if it is true, if it is then display the buffer, if it is false then dont
    COLORREF color = RGB(colorIn.bitValue[0],colorIn.bitValue[1],colorIn.bitValue[2]);
    int pixel {convertVector2FrameBuffer(position)};
    fa.memory[pixel] = color;
    return true;
}