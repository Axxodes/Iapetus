#pragma once
#include <string>
#include <array>
#include "renderer.hpp"

class Part
{
	public:
	std::string name {"Part"};
	Color3 color {};
	Vector3 position {};
    // std::array<std::array,8> vertices {};
};