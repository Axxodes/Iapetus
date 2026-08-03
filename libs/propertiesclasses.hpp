#pragma once
#include <array>
#include <string>

class Color3
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
	std::array<int,3> bitValue {blue, red, green};

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
		int r = hexToInt(hexValueIn.substr(0, 2));
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

    void print()
    {
        for (int value : bitValue)
	    {
    	    std::cout << value << ", ";
	    }
    }

    std::string get()
    {
        std::string output = "";
        for (int value : bitValue)
	    {
    	    output += std::to_string(value) + " ";
	    }
        return output;
    }
};