#pragma once
#include <array>
#include <string>
#include <cstdlib>

#include "math.hpp"
#include <cmath>

class Color3
{
	public:

	// values for the 255-type colors
	int red {};
	int green {};
	int blue {};

	void changeColor(int r,int g,int b) 
	{
		red = r;
		green = g;
		blue = b;
	}

	void changeColor(Color3 colorIn)
	{
		red = colorIn.red;
		green = colorIn.green;
		blue = colorIn.blue;
	}
};

Color3 substractColor3(Color3 color1, Color3 color2)
{
	Color3 returnColor {};
	returnColor.changeColor(color1.red-color2.red,color1.green-color2.green,color1.blue-color2.blue);
	return returnColor;
}

Color3 AddColor3(Color3 color1, Color3 color2)
{
	Color3 returnColor {};
	returnColor.changeColor(color1.red+color2.red,color1.green+color2.green,color1.blue+color2.blue);
	return returnColor;
}

Color3 MultiplyColor3(const Color3& color, double multiplier)
{
    Color3 result{};

    result.red = static_cast<int>(
        std::lround(color.red * multiplier)
    );

    result.green = static_cast<int>(
        std::lround(color.green * multiplier)
    );

    result.blue = static_cast<int>(
        std::lround(color.blue * multiplier)
    );

    return result;
}

Color3 MultiplyColor3(const Color3& color, int multiplier)
{
    Color3 result{};

    result.changeColor(
        color.red * multiplier,
        color.green * multiplier,
        color.blue * multiplier
    );

    return result;
}


