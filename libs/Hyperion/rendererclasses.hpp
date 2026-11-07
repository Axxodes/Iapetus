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

    Vector3 operator+(Vector3 vec2)
    {
        return Vector3(x+vec2.x,y+vec2.y,z+vec2.z);
    }

    Vector3 operator*(double multiplier) const
    {
        return {x*multiplier,y*multiplier,z*multiplier};
    }

    friend Vector3 operator*(double multiplier, Vector3 v)
    {
        return v*multiplier;
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

    Vector2 operator+(Vector2 vec2)
    {
        return Vector2(x+vec2.x,y+vec2.y);
    }

    Vector2 operator*(double multiplier) const
    {
        return {x*multiplier,y*multiplier};
    }

    friend Vector2 operator*(double multiplier, Vector2 v)
    {
        return v*multiplier;
    }
};