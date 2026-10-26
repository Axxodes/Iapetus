#pragma once
#include <array>
#include <string>
#include <cstdlib>

#include <vector>

using ButtonAction = void (*)();

struct Button
{
    uint32_t id {0};

    int x {};
    int y {};

    int width {};
    int height {};

    ButtonAction onClick;
};

int currentButtonCount {0};

std::vector<Button> buttonArray {};

std::vector<Button> returnButtonArray()
{
    return buttonArray;
}

std::vector<Button> addButton(int x, int y, int width, int height,ButtonAction buttonAction)
{

    Button button;
    button.id = currentButtonCount;
    button.x = x;
    button.y = y;
    button.width = width;
    button.height = height;
    button.onClick = buttonAction;

    buttonArray.push_back(button);
    currentButtonCount++;

    return buttonArray;
}

void buttonPrint()
{
    std::cout << "Button was clicked" << std::endl;
}

int syncCurrentButtonCount()
{
    return currentButtonCount;
}
