#pragma once
#include "propertiesclasses.hpp"
#include "renderer.hpp"
#include <windows.h>

void setPixelOnScreen(HDC window, int x, int y, Color3 color)
{
    COLORREF Color = RGB(color.bitValue[0],color.bitValue[1],color.bitValue[2]);
    SetPixel(window,x,y,Color);
}