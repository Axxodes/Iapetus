#pragma once

#include "math.hpp"
#include "propertiesclasses.hpp"
#include <windows.h>

// Incase this ever changes
constexpr double pi {3.141592653589793};

class Vector3 
{
    public:
	double x {};
	double y {};
	double z {};

	std::array<double,3> Value {x,y,z};

    void changeVector(double xIn,double yIn,double zIn)
    {
        x = xIn;
        y = yIn;
        z = zIn;
    }
    void changeX(double xIn)
    {
        x = xIn;
    }
    void changeY(double yIn)
    {
        y = yIn;
    }
    void changeZ(double zIn)
    {
        z = zIn;
    }
};

Vector3 vectorDotProduct(Vector3 vec1, Vector3 vec2)
{
    Vector3 output {};
    output.changeX(vec1.x*vec2.x);
    output.changeY(vec1.y*vec2.y);
    output.changeZ(vec1.z*vec2.z);
    return output;
}

Vector3 vectorAdd(Vector3 vec1, Vector3 vec2)
{
    Vector3 output{};
    output.changeX(vec1.x+vec2.x);
    output.changeY(vec1.y+vec2.y);
    output.changeZ(vec1.z+vec2.z);
    return output;
}

class Vector2
{
    public:
	double x {};
	double y {};

	std::array<double,2> Value {x,y};

    void changeVector(double xIn,double yIn)
    {
        x = xIn;
        y = yIn;
    }
    void changeX(double xIn)
    {
        x = xIn;
    }
    void changeY(double yIn)
    {
        y = yIn;
    }
};

Vector2 vectorDotProduct(Vector2 vec1, Vector2 vec2)
{
    Vector2 output {};
    output.changeX(vec1.x*vec2.x);
    output.changeY(vec1.y*vec2.y);
    return output;
}

Vector2 vectorAdd(Vector2 vec1, Vector2 vec2)
{
    Vector2 output{};
    output.changeX(vec1.x+vec2.x);
    output.changeY(vec1.y+vec2.y);
    return output;
}

class Vertex
{
    public:
    Vector3 position{};
};
