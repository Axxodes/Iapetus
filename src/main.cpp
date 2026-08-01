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

	int changeColor() 
	{
		if (bitValue.size == 6) 
		{

		}
	}
};

class Part
{
	public:
	std::string name {"Part"};
	color3 color {};
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