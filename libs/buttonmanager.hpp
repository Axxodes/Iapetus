#pragma once
#include <array>
#include <string>
#include <cstdlib>

#include <vector>

struct Button
{
    uint32_t id {0};

    int x {};
    int y {};

    int width {};
    int height {};
};

struct ButtonArray 
{
    size_t capacity;
    Button* memory;
};

int currentButtonCount1 {0};
int currentButtonCount2 {0};
int currentButtonCount3 {0};
int currentButtonCount4 {0};

int totalButtonCount {0};

ButtonArray setupButtonArray(size_t size)
{
    ButtonArray buttonArray {};
    buttonArray.memory = static_cast<Button*>(std::malloc(size*sizeof(Button)));

    if (!buttonArray.memory)
    {
        std::cout << "ButtonVectorX failed to allocate, trying again..." << std::endl;
        buttonArray.memory = static_cast<Button*>(std::malloc(size*sizeof(Button)));

        if (!buttonArray.memory)
        {
            std::cout << "ButtonVectorX failed to allocate twice, aborting..." << std::endl;
            return buttonArray;
        }
    }

    buttonArray.capacity = size;
    return buttonArray;
}

ButtonArray addButton(int x, int y, int width, int height,ButtonArray buttonArray1, int quadrant)
{
    if (quadrant != 1 && quadrant != 2 && quadrant != 3 && quadrant != 4)
    {
       return buttonArray1; 
    }

    if (quadrant == 1)
    {
        currentButtonCount1+=1;
        totalButtonCount+=1;

        Button button;
        button.id = totalButtonCount;
        button.x = x;
        button.y = y;
        button.width = width;
        button.height = height;

        buttonArray1.memory[currentButtonCount1-1] = button;
        return buttonArray1;
    }

    if (quadrant == 2)
    {
        currentButtonCount2+=1;
        totalButtonCount+=1;

        Button button;
        button.id = totalButtonCount;
        button.x = x;
        button.y = y;
        button.width = width;
        button.height = height;

        buttonArray1.memory[currentButtonCount2-1] = button;
        return buttonArray1;
    }

    if (quadrant == 3)
    {
        currentButtonCount3+=1;
        totalButtonCount+=1;

        Button button;
        button.id = totalButtonCount;
        button.x = x;
        button.y = y;
        button.width = width;
        button.height = height;

        buttonArray1.memory[currentButtonCount3-1] = button;
        return buttonArray1;
    }

    if (quadrant == 4)
    {
        currentButtonCount4+=1;
        totalButtonCount=+1;

        Button button;
        button.id = totalButtonCount;
        button.x = x;
        button.y = y;
        button.width = width;
        button.height = height;

        buttonArray1.memory[currentButtonCount4-1] = button;
        return buttonArray1;
    }

    return buttonArray1;
}

int syncCurrentButtonCount1()
{
    return currentButtonCount1;
}

int syncCurrentButtonCount2()
{
    return currentButtonCount2;
}

int syncCurrentButtonCount3()
{
    return currentButtonCount3;
}

int syncCurrentButtonCount4()
{
    return currentButtonCount4;
}