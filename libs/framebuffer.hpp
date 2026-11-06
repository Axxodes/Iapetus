#pragma once

#include <cstdlib>
#include <cstring>
#include <iostream>

#include "rendererclasses.hpp"
#include "propertiesclasses.hpp"
#include "macros.hpp"

#include <windows.h>

struct FrameBuffer
{
    size_t capacity {};
    uint32_t* memory;
};


// uint32_t foo = (long(a) << 24) | (long(b) << 16) | (long(c) << 8);

FrameBuffer fa {};

int width;
int height;

bool frameChanged {false};

void updateFrameBufferDimensions(int widthIn, int heightIn)
{
    width = widthIn;
    height = heightIn;
}

FrameBuffer createFrameBuffer(size_t size, int widthIn, int heightIn)
{
    fa.memory = (uint32_t*)std::malloc(size);
    if (!fa.memory)
    {
        OUTPUT_ERROR("Error, framebuffer failed to allocate, retrying...");
        fa.memory = (uint32_t*)std::malloc(size);

        if (!fa.memory)
        {
            OUTPUT_ERROR("Error, framebuffer failed to allocate twice, aborting...");
            return fa;
        }
    }

    fa.capacity = size;
    memset(fa.memory, 0, size);

    width = widthIn;
    height = heightIn;

    frameChanged = true;

    return fa;
}

FrameBuffer reAllocFrameBuffer(size_t size, int widthIn, int heightIn)
{
    if (!fa.memory)
    {
        OUTPUT_ERROR("Error, try to re-allocate non-allocated buffer!");
        return fa;
    }
    else
    {
        uint32_t* tempFrameBufferMemoryPointer = (uint32_t*)std::malloc(size);

        if (tempFrameBufferMemoryPointer)
        {
            std::free(fa.memory);

            fa.memory = tempFrameBufferMemoryPointer;

            fa.capacity = size;
            memset(fa.memory, 0, size);

            width = widthIn;
            height = heightIn;

            frameChanged = true;

            return fa;
        }
        
        OUTPUT_ERROR("Error, framebuffer failed to re-allocate, aborting...");
        //i know this doesnt align with the original allocater where it attempts it twice but i'll add this later
        return fa;
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

bool changeFrameBufferValue(int byte, uint32_t color)
{
    fa.memory[byte] = color;
    frameChanged = true;

    return true;
}

bool changePixel(int x, int y, Color3 colorIn)
{
    uint32_t color = (colorIn.red) << 16|(colorIn.green) << 8|(colorIn.blue);
    int pixel {convertCoordsFrameBuffer(x,y)};
    changeFrameBufferValue(pixel,color);
    return true;
}

bool changePixel(Vector2 position, Color3 colorIn)
{
    uint32_t color = (colorIn.red) << 16|(colorIn.green) << 8|(colorIn.blue);
    int pixel {convertVector2FrameBuffer(position)};
    changeFrameBufferValue(pixel,color);
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
        uint32_t color = fa.memory[convertVector2FrameBuffer(position)];

        returnColor.changeColor((color >> 16) & 0xFF,(color >> 8) & 0xFF,(color) & 0xFF);
        return returnColor;
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
        uint32_t color = fa.memory[convertCoordsFrameBuffer(x,y)];

        returnColor.changeColor((color >> 16) & 0xFF,(color >> 8) & 0xFF,(color) & 0xFF);
        return returnColor;
    }

    return returnColor;
}

void returnFrame()
{
    frameChanged = true; //tell the window
    return;
}