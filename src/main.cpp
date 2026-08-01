#include <iostream>
#include <string>
// #include <GLFW/glfw3.h>

class Part
{
	public:
	std::string name {"Part"};
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