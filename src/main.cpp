#include <iostream>
#include <GLFW/glfw3.h>

int main()
{
	int x{};
	int y{};

	std::cout << "Enter two numbers seperated by a space:" << "\n";

	std::cin >> x >> y;

	std::cout << "You chose: " << x << " and " << y << "\n";

	std::cout << sizeof(int);

    return 0;
}