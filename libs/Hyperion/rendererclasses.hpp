#pragma once

#include "math.hpp"
#include "propertiesclasses.hpp"
#include <windows.h>

struct Vector3 
{
 
	double x {};
	double y {};
	double z {};

    void changeVector(double xIn,double yIn,double zIn)
    {
        x = xIn;
        y = yIn;
        z = zIn;
    }
};

struct Vector2
{
	double x {};
	double y {};

    void changeVector(double xIn,double yIn)
    {
        x = xIn;
        y = yIn;
    }
};

double vectorDotProduct(Vector3 vec1, Vector3 vec2)
{
    double output {vec1.x*vec2.x+vec1.y*vec2.y+vec1.z*vec2.z};
    return output;
}

Vector3 vectorAdd(Vector3 vec1, Vector3 vec2)
{
    Vector3 output{};
    output.x = vec1.x+vec2.x;
    output.y = vec1.y+vec2.y;
    output.z = vec1.z+vec2.z;
    return output;
}

double vectorDotProduct(Vector2 vec1, Vector2 vec2)
{
    double output {vec1.x*vec2.x+vec1.y*vec2.y};
    return output;
}

Vector2 vectorAdd(Vector2 vec1, Vector2 vec2)
{
    Vector2 output{};
    output.x = vec1.x+vec2.x;
    output.y = vec1.y+vec2.y;
    return output;
}