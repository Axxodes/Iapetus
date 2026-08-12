#pragma once
#include "propertiesclasses.hpp"
#include "rendererclasses.hpp"
#include <windows.h>
#include <cmath>
#include "objects.hpp"
#include "framebuffer.hpp"

// Incase this ever changes
constexpr double pi {3.141592653589793};

void setPixelOnScreen(int x, int y, Color3 colorIn)
{
    Vector2 position {};
    position.changeVector(x,y);
    changePixel(position,colorIn);
}

void generateCircle(int radius, Color3 color)
{
    for (int i=0;i<10;i++)
	{
		setPixelOnScreen(50+i,50,color);
	}
}

void drawLine(HDC window, Vector2 vec1, Vector2 vec2, Color3 color)
{
    double m = static_cast<double>(vec2.y - vec1.y) / static_cast<double>(vec2.x - vec1.x);

    double c = vec1.y - m * vec1.x;

    for (int x = vec1.x; x <= vec2.x; x++)
    {
        int y = static_cast<int>(round(m * x + c));
        setPixelOnScreen(x, y, color);
    }
}

void drawCube(Vector2 rootPos, Color3 color)
{
    
}

void drawSine(Vector2 rootPos, Color3 color)
{
    
}