#pragma once
#include "propertiesclasses.hpp"
#include "rendererclasses.hpp"
#include <windows.h>
#include <cmath>
#include "objects.hpp"
#include "framebuffer.hpp"
#include "math.hpp"

extern HWND window;

int widthRenderer {};
int heightRenderer {};

void updateRenderDimensions(int widthIn, int heightIn)
{
    widthRenderer = widthIn;
    heightRenderer = heightIn;
}

#include <iostream>

// Incase this ever changes
constexpr double pi {3.141592653589793};

void setPixelOnScreen(int x, int y, Color3 colorIn)
{
    if (0 > x or 0 > y)
    {
        return;
    }

    if (x < widthRenderer and y < heightRenderer)
    {
        changePixel(x,y,colorIn);
        return;
    }

    std::cout << "Tried to set color for out of bounds pixel, returning blank color.";
}

void drawCircle(Vector2 midpoint,int radius, Color3 color)
{
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

    double m = static_cast<double>(vec2.y - vec1.y) / static_cast<double>(vec2.x - vec1.x);
    double c = vec1.y - m * vec1.x;
    
    if (abs(vec2.y - vec1.y) < abs(vec2.x - vec1.x))
    {
        for (int x = vec1.x; x <= vec2.x; x++)
        {
            double exacty = static_cast<double>(m * x + c);

            int y = static_cast<int>(floor(exacty));

            double dist = exacty - std::floor(exacty);

            Color3 grad1Color = getGradient(getPixelColor(x,y),color,1-dist);
            Color3 grad2Color = getGradient(getPixelColor(x,y+1),color,dist);

            setPixelOnScreen(x, y, grad1Color);
            setPixelOnScreen(x, y+1, grad2Color);
        }
    }
    else
    {
        for (int y = vec1.y; y <= vec2.y; y++)
        {
            double exactx = static_cast<double>((y - c) / m);

            int x = static_cast<int>(floor(exactx));

            double dist = exactx - std::floor(exactx);

            Color3 grad1Color = getGradient(getPixelColor(x,y),color,1-dist);
            Color3 grad2Color = getGradient(getPixelColor(x+1,y),color,dist);

            setPixelOnScreen(x, y, grad1Color);
            setPixelOnScreen(x+1, y, grad2Color);
        }
    }
}

void drawCube(Vector2 rootPos, Color3 color)
{

}

void drawSine(Vector2 rootPos, Color3 color)
{
    
}