#include <string>
#include <array>
#include <fstream>
#include <iostream>
#include "renderer.hpp"
#include <ctime>


void log(std::string message)
{
    time_t timestamp;
    time(&timestamp);
    std::fstream file {};
    file.open("logs.txt");
    if (file.is_open())
    {
        file << "[LOG] " << message;
    }
}

int searchLetterInFile(char input)
{
    std::fstream file {};
    file.open("libs/Hyperion/Fonts/Default.txt");
    if (file.is_open())
    {
       char currentLetter {};
       for (int i=0;i<=50;i++)
       {
            currentLetter = file.get();
            if (currentLetter == input)
            {
                file.close();
                return i;
            }
       }
       return -1;
    }
    return 0;
}

void openFontLetter(char letter)
{
    //open file
    std::fstream file {};
    file.open("libs/Hyperion/Fonts/Default.txt");

    /*std::fstream log {};
    log.open("logs.txt");*/

    char x = 'E';
    char* charptr {&x};

    if (file.is_open())
    {
        int letterE = searchLetterInFile(letter);
        file.seekg(letterE);
        file.get(charptr,2,'.');
        
        log("Letter has been found");

        file.close();
    }
}