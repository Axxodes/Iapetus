#include <iostream>
#include <string>
#include "../libs/math.hpp"
#include <array>
#include "../libs/materialmanager.hpp"
#include "../libs/propertiesclasses.hpp"
#include "../libs/objects.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main()
{
	Part myPart;

	myPart.color.changeColor(255,255,255);
	myPart.color.print();

	return 0;
}