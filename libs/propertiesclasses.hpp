#pragma once
#include <array>
#include <string>
#include <cstdlib>

#include "math.hpp"
#include <cmath>

#include <cstdint>

struct Color3
{

	// values for the 255-type colors
	uint8_t red {};
	uint8_t green {};
	uint8_t blue {};

	void changeColor(std::uint8_t r,std::uint8_t g,std::uint8_t b) 
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

	Color3 operator-(Color3 other)
	{
		Color3 returnColor {};
		returnColor.changeColor(red-other.red,green-other.green,blue-other.blue);
		return returnColor;
	}

	Color3 operator+(Color3 other)
	{
		Color3 returnColor {};
		returnColor.changeColor(red+other.red,green+other.green,blue+other.blue);
		return returnColor;
	}

	Color3 operator*(double multiplier)
	{
    	Color3 result{};

    	result.red = static_cast<uint8_t>(std::lround(red * multiplier));
    	result.green = static_cast<uint8_t>(std::lround(green * multiplier));
    	result.blue = static_cast<uint8_t>(std::lround(blue * multiplier));

    	return result;
	}

	Color3 operator*(int multiplier)
	{
    	Color3 result{};

    	result.changeColor(red*multiplier,green*multiplier,blue*multiplier);

    	return result;
	}

	bool operator!=(Color3 other)
	{
		if (red != other.red || blue != other.blue || green != other.green)
		{
			return true;
		}
		return false;
	}

	bool operator==(Color3 other)
	{
		if (red == other.red && blue == other.blue && green == other.green)
		{
			return true;
		}
		return false;
	}
};








