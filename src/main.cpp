#include <iostream>

int main()
{
	int x{};
	int y{};

	std::cout << "Enter two numbers seperated by a space:" << "\n";

	std::cin >> x >> y;

	std::cout << "You chose: " << x << " and " << y << "\n";

    return 0;
}