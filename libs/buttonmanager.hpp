#pragma once
#include <array>
#include <string>
#include <cstdlib>

#include <vector>

using ButtonAction = void (*)();

struct Button
{
    long id {0};

    int x {};
    int y {};

    int width {};
    int height {};

    Color3 color {255,255,255};

    ButtonAction onClick;

    void changePos(int xIn, int yIn)
    {
        x = xIn;
        y = yIn;
    }
};

int currentButtonCount {0};

std::vector<Button> buttonArray {};

std::vector<Button> returnButtonArray()
{
    return buttonArray;
}

std::vector<Button> addButton(int x, int y, int width, int height,Color3 color,ButtonAction buttonAction)
{
    Button button;
    button.id = currentButtonCount;
    button.x = x;
    button.y = y;
    button.width = width;
    button.height = height;
    button.color = color;
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
