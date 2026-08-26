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
int height {};

FrameBuffer createFrameBuffer(size_t size, int widthIn, int heightIn)
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
    height = heightIn;

    return fa;
}

FrameBuffer reAllocFrameBuffer(size_t size, int widthIn, int heightIn)
{
    if (!fa.memory)
    {
        return fa;
    }
    else
    {
        COLORREF* tempFrameBuffer = (COLORREF*)std::malloc(size);

        if (tempFrameBuffer)
        {
            std::free(fa.memory);

            fa.memory = tempFrameBuffer;

            fa.capacity = size;
            memset(fa.memory, 0, size);

            width = widthIn;
            height = heightIn;

            return fa;
        }
        
        std::cout << "Error, framebuffer failed to allocate.";
        return fa;
    }
}

void testFillFrameBuffer()
{
    COLORREF color = RGB(0,0,0);
    for (int i=0;i<fa.capacity/4-1;i++)
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

int convertCoordsFrameBuffer(int x, int y)
{
    if (width)
    {
        return y * width + x;
    }
    return 0;
}

bool changePixel(int x, int y, Color3 colorIn)
{
    // the return bool is checked in window.hpp, set a variable to this return and check if it is true, if it is then display the buffer, if it is false then dont
    COLORREF color = RGB(colorIn.red,colorIn.green,colorIn.blue);
    int pixel {convertCoordsFrameBuffer(x,y)};
    fa.memory[pixel] = color;
    return true;
}

bool changePixel(Vector2 position, Color3 colorIn)
{
    // the return bool is checked in window.hpp, set a variable to this return and check if it is true, if it is then display the buffer, if it is false then dont
    COLORREF color = RGB(colorIn.red,colorIn.green,colorIn.blue);
    int pixel {convertVector2FrameBuffer(position)};
    fa.memory[pixel] = color;
    return true;
}

Color3 getPixelColor(Vector2 position)
{
    Color3 returnColor {};

    if (0 > position.x || 0 > position.y)
    {
        return returnColor;
    }
    if (position.x < width && position.y < height)
    {
        int gridPos = convertVector2FrameBuffer(position);

        COLORREF color = fa.memory[gridPos];

        int r = GetRValue(color);
        int g = GetGValue(color);
        int b = GetBValue(color);

        returnColor.changeColor(r,g,b);
    }

    return returnColor;
}

Color3 getPixelColor(int x, int y)
{
    Color3 returnColor {};

    if (0 > x || 0 > y)
    {
        return returnColor;
    }

    if (x < width && y < height)
    {
        int gridPos = convertCoordsFrameBuffer(x,y);

        COLORREF color = fa.memory[gridPos];

        int r = GetRValue(color);
        int g = GetGValue(color);
        int b = GetBValue(color);

        returnColor.changeColor(r,g,b);
    }

    return returnColor;
}