#pragma once

#include "math.hpp"
#include "objects.hpp"
#include "propertiesclasses.hpp"
#include "window.hpp"
#include <windows.h>

struct Vector3 
{
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

Vector3 dotProduct(Vector3 vec1, Vector3 vec2)
{
    Vector3 output {};
    output.changeX(vec1.x*vec2.x);
    output.changeY(vec1.y*vec2.y);
    output.changeZ(vec1.z*vec2.z);
    return output;
}

class Vertex
{
    public:
    Vector3 position{};
};