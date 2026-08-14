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
        file << message << "[LOG]" << '\n';
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

void openFontLetter(char letter) // FIX THIS
{
    //open file
    std::fstream file {};
    file.open("libs/Hyperion/Fonts/Default.txt");

    /*std::fstream log {};
    log.open("logs.txt");*/

    std::string fontLetter {};

    if (file.is_open())
    {
        int letterE = searchLetterInFile(letter);
        file.seekg(letterE);
        std::getline(file, fontLetter, '.'); //filestream

        std::stringstream ss{fontLetter};
        
        std::string part {};

        while(std::getline(ss,part,':'))
        {
            if (std::string str(1, letter) == part)
            {
                ss = part;
            }
        }

        int count {};

        while(std::getline(ss,part,';')) // stringstream
        {
            count+=1
        }

        std::array<std::string,count> lines {};

        count=0;

        while(std::getline(ss,part,';'))
        {
            lines[count] = part;
            count+=1;
        }

        file.close();
    }
}