#pragma once
#include <string>

class vector3 
{
	public:
	double x {};
	double y {};
	double z {};

	std::array <double, 3> value {x,y,z};
};

inline double Power(double num, int power)
{
    double result = 1;
    for(int i = 0; i < power; i++)
    {
        result *= num;
    }
    return result;
}

inline double Root(double number, int root)
{
    double guess = number / root;
    for(int i = 0; i < 50; i++)
    {
        guess = ((root - 1) * guess + number / Power(guess, root - 1)) / root;
    }
    return guess;
}

inline double Squared(double num)
{
    return num * num;
}

inline double Distance2D(int x1, int y1, int x2, int y2)
{
    return Root(Squared(x2-x1) + Squared(y2-y1),2);
}

inline double Distance3D(int x1, int y1, int z1,int x2, int y2, int z2)
{
    return Root(Squared(x2-x1)+Squared(y2-y1)+Squared(z2-z1),2);
}

inline int hexToInt(const std::string& hex)
{
    return std::stoi(hex, nullptr, 16);
}