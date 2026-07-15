#include <iostream>
#include <GLFW/glfw3.h>

int refDoSomething() 
{
	int x {};

	std::cin >> x;

	return x;
}

int main()
{
	int num{ refDoSomething() };
	
	std::cout << num*2 << "\n";
}