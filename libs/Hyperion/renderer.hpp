#pragma once

#include "propertiesclasses.hpp"
#include "rendererclasses.hpp"

#include <windows.h>

#include "framebuffer.hpp"
#include "buttonmanager.hpp"
#include "objectmanager.hpp"

#include <cmath>
#include "math.hpp"
#include <cstdlib>

#include <thread>
#include <iostream>

#include <algorithm>
#include <array>

extern HWND window;

int widthRenderer {};
int heightRenderer {};

void updateRenderDimensions(int widthIn, int heightIn)
{
    widthRenderer = widthIn;
    heightRenderer = heightIn;
}

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
}

Color3 getGradient(const Color3& background,const Color3& lineColor,double coverage)
{
    coverage = std::clamp(coverage, 0.0, 1.0);

    const auto blend = [coverage](std::uint8_t bg, std::uint8_t line)
    {
        const double value = bg + (static_cast<double>(line) - bg) * coverage;
        return static_cast<std::uint8_t>(std::clamp(std::lround(value), 0L, 255L));
    };

    return {blend(background.red,lineColor.red),blend(background.green,lineColor.green),blend(background.blue, lineColor.blue)};
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
            p+=2*(x+y)+1;
        }
        else
        {
            p+=2*x+1;
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

void drawLine(Vector2 vec1, Vector2 vec2, Color3 color)
{
    const double x1 = static_cast<double>(vec1.x);
    const double y1 = static_cast<double>(vec1.y);
    const double dx = static_cast<double>(vec2.x) - x1;
    const double dy = static_cast<double>(vec2.y) - y1;

    const double span = std::max(std::abs(dx), std::abs(dy));

    if (span == 0.0)
    {
        setPixelOnScreen(vec1.x, vec1.y, color);
        return;
    }

    const int steps = static_cast<int>(std::ceil(span));
    const bool xMajor = std::abs(dx) >= std::abs(dy);

    for (int step = 0; step <= steps; ++step)
    {
        const double t = static_cast<double>(step) / steps;
        const double exactX = x1 + dx * t;
        const double exactY = y1 + dy * t;

        if (xMajor)
        {
            const int x = static_cast<int>(std::floor(exactX));
            const int y = static_cast<int>(std::floor(exactY));
            const double fraction = exactY - y;

            setPixelOnScreen(
                x, y,
                getGradient(getPixelColor(x, y), color, 1.0 - fraction));
            setPixelOnScreen(
                x, y + 1,
                getGradient(getPixelColor(x, y + 1), color, fraction));
        }
        else
        {
            const int x = static_cast<int>(std::floor(exactX));
            const int y = static_cast<int>(std::floor(exactY));
            const double fraction = exactX - x;

            setPixelOnScreen(
                x, y,
                getGradient(getPixelColor(x, y), color, 1.0 - fraction));
            setPixelOnScreen(
                x + 1, y,
                getGradient(getPixelColor(x + 1, y), color, fraction));
        }
    }
}

void bresenhamLineDraw(int x1, int y1, int x2, int y2, Color3 color)
{
    const int dx = std::abs(x2 - x1);
    const int sx = (x1 < x2) ? 1 : -1;
    const int dy = -std::abs(y2 - y1);
    const int sy = (y1 < y2) ? 1 : -1;
    int err = dx + dy;

    while (true)
    {
        setPixelOnScreen(x1, y1, color);

        if (x1 == x2 && y1 == y2)
            break;

        const int e2 = 2 * err;

        if (e2 >= dy)
        {
            err += dy;
            x1 += sx;
        }
        if (e2 <= dx)
        {
            err += dx;
            y1 += sy;
        }
    }
}

void drawBezierCurve(Vector2 pos1, Vector2 pos2, Vector2 anchor, int res)
{
    for(int i{0};i<res;i++)
    {
        double t;
        if(i!=0) t = static_cast<double>(i)/res;
        else t=0;

        Vector2 pixelPos = (1-t)*((1-t)*pos1+(t*anchor))+t*((1-t)*anchor+t*pos2);
        setPixelOnScreen(pixelPos.x,pixelPos.y,Color3(255,255,255));
    }
}

void drawRectangle(Vector2 position,int sizeX,int sizeY,Color3 color)
{
    for (int x=0;x<sizeX;x++)
    {
        for (int y=0;y<sizeY;y++)
        {
            setPixelOnScreen(x+position.x,y+position.y,color);
        }
    }
}

void drawCube(Vector2 rootPos, Color3 color); // define ts later bro i dont wanna rn

void renderButtons(std::vector<Button> buttonArray,int buttonAmount)
{
    for(int i {0};i<buttonAmount;i++)
    {
        Button button = buttonArray[i];

        for(int x{0};x<button.width;x++)
        {
            for(int y{0};y<button.height;y++)
            {
                setPixelOnScreen(button.x+x,button.y+y,button.color);
            }
        }
    }

    std::cout << "RenderButtons finished" << std::endl;
}

void rayCast(Vector3 cameraPos /* ,std::vector<PolyMesh> object*/)
{
    // widthRenderer, heightRenderer

    std::array<Vector3,100> cameraRayPoints;
    int count {};
    for(auto x{0};x<10;x++)
    {
        // get a point on the grid
        for(auto y{0};y<10;y++)
        {
            cameraRayPoints[count] = Vector3{std::round(cameraPos.x+x),std::round(cameraPos.y+y),cameraPos.z};
            count++;
        }
    }

    // cast rays from all the the points in cameraRayPoints
}

void renderloop(std::vector<Button> buttonArray,int buttonAmount)
{
    std::cout << "Renderer.hpp says: "<< widthRenderer << ',' << heightRenderer << std::endl;

    renderButtons(buttonArray,buttonAmount);
    
    std::cout << "Renderloop finished" << std::endl;
}