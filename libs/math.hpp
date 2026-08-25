#pragma once
#include <string>
#include <array>

long map(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

double map(double x, double in_min, double in_max, double out_min, double out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

inline double power(double num, int power)
{
    double result = 1;
    for(int i = 0; i < power; i++)
    {
        result *= num;
    }
    return result;
}

inline double root(double number, int root)
{
    double guess = number / root;
    for(int i = 0; i < 50; i++)
    {
        guess = ((root - 1) * guess + number / power(guess, root - 1)) / root;
    }
    return guess;
}

inline double squared(double num)
{
    return num * num;
}

inline double distance2D(int x1, int y1, int x2, int y2)
{
    return root(squared(x2-x1) + squared(y2-y1),2);
}

inline double distance3D(int x1, int y1, int z1,int x2, int y2, int z2)
{
    return root(squared(x2-x1)+squared(y2-y1)+squared(z2-z1),2);
}

inline int hexToInt(const std::string& hex)
{
    return std::stoi(hex, nullptr, 16);
}