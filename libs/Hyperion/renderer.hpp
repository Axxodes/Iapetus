#pragma once
#include "propertiesclasses.hpp"
#include "rendererclasses.hpp"
#include <windows.h>
#include <cmath>
#include "objects.hpp"

void setPixelOnScreen(HDC window, int x, int y, Color3 color)
{
    COLORREF Color = RGB(color.bitValue[0],color.bitValue[1],color.bitValue[2]);
    SetPixel(window,x,y,Color);
}

void generateCircle(HDC subwindow, int radius, Color3 color)
{
    for (int i=0;i<10;i++)
	{
		setPixelOnScreen(subwindow,50+i,50,color);
	}
}

void drawLine(HDC window, Vector2 vec1, Vector2 vec2, Color3 color)
{
    double m = static_cast<double>(vec2.y - vec1.y) /
               static_cast<double>(vec2.x - vec1.x);

    double c = vec1.y - m * vec1.x;

    for (int x = vec1.x; x <= vec2.x; x++)
    {
        int y = static_cast<int>(round(m * x + c));
        setPixelOnScreen(window, x, y, color);
    }
}

void drawCube(HDC window, Vector2 rootPos, Color3 color)
{

}

void drawSine(HDC window,Color3 color)
{
    
}