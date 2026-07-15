#include <iostream>
#include <GLFW/glfw3.h>

int getscreensize() 
{
	int x {};

	std::cin >> x;

	return x;
}

int main()
{
	int ss {getscreensize()};

	std::cout << ss << '\n';
}