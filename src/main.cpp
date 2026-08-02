#include <iostream>
#include <string>
#include "../libs/math.hpp"
#include <array>
#include "../libs/materialmanager.hpp"
#include "../libs/propertiesclasses.hpp"
#include "../libs/objects.hpp"

// #include <GLFW/glfw3.h>

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