#pragma once
#include <array>
#include <string>

#include <vector>

enum class quadrant {I, II, III, IV};

struct Button
{
    std::string name {};

    int x {};
    int y {};

    int width {};
    int height {};

    quadrant buttonQuadrant;
};

std::vector<Button> setupButtonArray(std::size_t count)
{
    return std::vector<Button>(count);
}