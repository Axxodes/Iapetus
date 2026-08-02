#include <iostream>
#include <string>
#include "../libs/math.hpp"
#include <array>
#include "..libs/materialmanager.hpp"

// #include <GLFW/glfw3.h>

class vector3 
{
	public:
	double x {};
	double y {};
	double z {};

	std::array <double, 3> value {x,y,z};
};

class color3
{
	private:

	// values for the 255-type colors
	int red {};
	int green {};
	int blue {};

	public:

	// just store the hex value and shi
	std::string hexValue {};
	
	// actual array used by people
	std::array<int, 3> bitValue {blue, red, green};

	bool changeColor(int r,int g,int b) 
	{
		if (bitValue.size() == 3)
		{
			bitValue[0] = r;
			bitValue[1] = g;
			bitValue[2] = b;
			return true;
		}
		else 
		{
			return false;
		}
	}

	bool changeHexColor(std::string hexValueIn)
	{
	   if (hexValueIn.length() == 6) 
	   {
		int r = hexToInt(HexValueIn.substr(0, 2));
   		int g = hexToInt(hexValueIn.substr(2, 2));
    	int b = hexToInt(hexValueIn.substr(4, 2));

		std::array<int,3> tempArr {r,g,b};
		bitValue = tempArr;
		hexValue = hexValueIn;
		return false;
	   }
	   else
	   {
		return true;
	   }
	}
};

class Part
{
	public:
	std::string name {"Part"};
	color3 color {};
	vector3 position {};
};

int main()
{
	Part part;

	part.color.changeColor(255,255,255);

	for (int value : part.color.bitValue)
	{
    	std::cout << value << ", ";
	}

	return 0;
}