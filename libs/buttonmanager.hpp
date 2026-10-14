#pragma once
#include <array>
#include <string>
#include <cstdlib>

#include <vector>

struct Button
{
    uint32_t id {};

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

ButtonArray setupButtonArray(size_t size)
{
    ButtonArray buttonArray {};
    buttonArray.memory = static_cast<Button*>(malloc(size*sizeof(Button)));

    if (!buttonArray.memory)
    {
        std::cout << "ButtonVectorX failed to allocate, trying again..." << std::endl;

        ButtonArray buttonArray {};
        buttonArray.memory = static_cast<Button*>(malloc(size*sizeof(Button)));

        if (!buttonArray.memory)
        {
            std::cout << "ButtonVectorX failed to allocate twice, aborting..." << std::endl;
            return buttonArray;
        }
    }

    buttonArray.capacity = size;
    return buttonArray;
}