#pragma once
#include "propertiesclasses.hpp"
#include "rendererclasses.hpp"
#include <windows.h>
#include <cmath>
#include "objects.hpp"
#include "framebuffer.hpp"
#include "math.hpp"

extern HWND window;


int width = rect.right - rect.left;
int height = rect.bottom - rect.top;

#include <iostream>

// Incase this ever changes
constexpr double pi {3.141592653589793};

void setPixelOnScreen(int x, int y, Color3 colorIn)
{

    if (0 > x or 0 > y)
    {
        return;
    }

    if (x < width and y < height)
    {
        Vector2 position {};
        position.changeVector(x,y);
        changePixel(position,colorIn);
        return;
    }
}

void generateCircle(Vector2 midpoint,int radius, Color3 color)
{
    HDC subwindow = GetDC(window);
	RECT rect;
	GetClientRect(window, &rect);

	width = rect.right - rect.left;
	height = rect.bottom - rect.top;

    ReleaseDC(window,subwindow);

    int x {0};
    int y {-radius};
    int p {-radius};

    while (x < -y)
    {
        if (p>0)
        {
            y+=1;
            p+= 2*(x+y) + 1;
        }
        else
        {
            p+= 2*x+1; 
        }

        setPixelOnScreen(midpoint.x+x, midpoint.y+y, color);
        setPixelOnScreen(midpoint.x-x, midpoint.y+y, color);
        setPixelOnScreen(midpoint.x+x, midpoint.y-y, color);
        setPixelOnScreen(midpoint.x-x, midpoint.y-y, color);

        setPixelOnScreen(midpoint.x+y, midpoint.y+x, color);
        setPixelOnScreen(midpoint.x+y, midpoint.y-x, color);
        setPixelOnScreen(midpoint.x-y, midpoint.y+x, color);
        setPixelOnScreen(midpoint.x-y, midpoint.y-x, color);
        x+=1;
    }
}

Color3 getGradient(Color3 color1, Color3 color2, double gradPercentage)
{
   Color3 output {};
   output = AddColor3(color1,MultiplyColor3(substractColor3(color2,color1),gradPercentage));
   return output;
}

void drawLine(Vector2 vec1, Vector2 vec2, Color3 color)
{
    HDC subwindow = GetDC(window);
	RECT rect;
	GetClientRect(window, &rect);

	width = rect.right - rect.left;
	height = rect.bottom - rect.top;

    ReleaseDC(window,subwindow);
    double m = static_cast<double>(vec2.y - vec1.y) / static_cast<double>(vec2.x - vec1.x);

    double c = vec1.y - m * vec1.x;
    if (abs(vec2.y - vec1.y) < abs(vec2.x - vec1.x))
    {
        for (int x = vec1.x; x <= vec2.x; x++)
        {
            double exacty = static_cast<double>(m * x + c);

            int y1 = static_cast<int>(floor(exacty));
            int y2 = y1+1;

            double fraction = exacty - std::floor(exacty);

            double percent = 1-fraction;

            Color3 grad1Color = getGradient(getPixelColor(x,y1),color,percent);
            Color3 grad2Color = getGradient(getPixelColor(x,y2),color,fraction);

            setPixelOnScreen(x, y1, grad1Color);
            setPixelOnScreen(x, y2, grad2Color);
        }
    }
    else
    {
        for (int y = vec1.y; y <= vec2.y; y++)
        {
            double exactx = static_cast<double>((y - c) / m);

            int x1 = static_cast<int>(floor(exactx));
            int x2 = x1+1;

            double fraction = exactx - std::floor(exactx);

            double percent = 1-fraction;

            Color3 grad1Color = getGradient(getPixelColor(x1,y),color,percent);
            Color3 grad2Color = getGradient(getPixelColor(x2,y),color,fraction);

            setPixelOnScreen(x1, y, grad1Color);
            setPixelOnScreen(x2, y, grad2Color);
        }
    }
}

void drawCube(Vector2 rootPos, Color3 color)
{
    HDC subwindow = GetDC(window);
	RECT rect;
	GetClientRect(window, &rect);

	width = rect.right - rect.left;
	height = rect.bottom - rect.top;

    ReleaseDC(window,subwindow);
    
}

void drawSine(Vector2 rootPos, Color3 color)
{
    HDC subwindow = GetDC(window);
	RECT rect;
	GetClientRect(window, &rect);

	width = rect.right - rect.left;
	height = rect.bottom - rect.top;

    ReleaseDC(window,subwindow);
    
}