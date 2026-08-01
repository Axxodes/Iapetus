#include <iostream>
#include <string>
#include "../libs/math.hpp"

// #include <GLFW/glfw3.h>

class vector3 
{
	public:
	double x {};
	double y {};
	double z {};
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
	std::array<int, 3> bitValue {{blue, red, green}};

	int changeColor(r,g,b) 
	{
		if (bitValue.size == 6) 
		{
			bitValue[0] = r;
			bitValue[1] = g;
			bitValue[2] = b;
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
	int* p = new int(5);
	int& x {*p};
	std::cout << x << "\n";
	*p = 10;
	std ::cout << x << "\n";
	delete p;
	p = nullptr;
	
	Part part;
}