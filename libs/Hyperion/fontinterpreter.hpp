#include <string>
#include <array>
#include <fstream>
#include <iostream>
#include "renderer.hpp"

int searchLetterInFile(char input)
{
    std::fstream file {};
    file.open("libs/Hyperion/Fonts/Default.txt");
    if (file.is_open())
    {
       char currentLetter {};
       for (int i=0;i>=50;i++)
       {
            
       }
    }
}

void openFont()
{
    //open file
    std::fstream file {};
    file.open("libs/Hyperion/Fonts/Default.txt");

    /*std::fstream log {};
    log.open("logs.txt");*/



    if (file.is_open())
    {
        std::string letter;
        getline(file,letter,'.');



        file.close();
    }
}