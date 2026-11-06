#pragma once

#include <vector>
#include <iostream>

#include "renderer.hpp"
#include "filehandler.hpp"

struct Line
{
    Vector2 start;
    Vector2 end;
};

struct Character
{
    uint8_t fontId {};
    std::vector<Line> lines;

    void drawCharToScreen(int size, Vector2 origin)
    {
        int vectorSize = static_cast<int>(lines.size());
        for(int i{0};i<vectorSize;i++)
        {
            bresenhamLineDraw((lines[i].start.x*size+origin.x),(lines[i].start.y*size+origin.y),(lines[i].end.x*size+origin.x),(lines[i].end.y*size+origin.y),Color3{255,255,255});
        }
    }
};

struct LetterArray
{
    std::vector<Character> characters;
};

LetterArray letterArray {};

void drawAllFontChars(Vector2 origin)
{
    for(size_t i{0};i<letterArray.characters.size();i++)
    {
        letterArray.characters[i].drawCharToScreen(3,Vector2(origin.x+(13*i),origin.y/*+(13*static_cast<int>(i/10))*/));
    }
}

void constructFontChar(int fontId,std::vector<Line> lines)
{
    Character character {};
    character.lines = lines;
    character.fontId = fontId;

    // character.drawCharToScreen(5,Vector2(20,20));
    letterArray.characters.push_back(character);
}

void openFont(const wchar_t* name)
{
    auto fileName = std::wstring(name) + L".txt";
    static int fontCount {1};
    
    if(!loadFontIntoFileBuffer(fileName.c_str()))
    {
        return;
    }

    int totalGlyphs{0};

    for(size_t i{0};i<fileBuffer.used;i++)
    {
        char letter = static_cast<char>(fileBuffer.memory[i]);
        if(letter == '\n')
        {
            totalGlyphs++;
        }
    }

    int prevGlyphEnd{0};

    for(int count{0};count<totalGlyphs;count++)
    {
        // change this so it advances to the next line, every iteration.
        int totalLines {0};

        for(size_t i{0};i<fileBuffer.used;i++)
        {
            if(static_cast<int>(i)<prevGlyphEnd)
            {
                continue;
            }
            char letter = static_cast<char>(fileBuffer.memory[i]);
            if(letter == ',')
            {
                totalLines++;
            }
            if(letter == '\n')
            {
                break;
            }
        }

        std::vector<Line> letterLines(totalLines);

        bool onXCoord {true};
        bool onStartCoord {true};
        int currentLine {0};

        for(size_t i{1};i<fileBuffer.used;i++)
        {
            if(static_cast<int>(i)<prevGlyphEnd)
            {
                continue;
            }
            char character = static_cast<char>(fileBuffer.memory[i]);

            if (character >= '0' && character <= '9')
            {
                double value = character - '0';

                if(onXCoord == true)
                {
                    if(onStartCoord == true)
                    {
                        letterLines[currentLine].start.x = value+1;
                    }
                    else
                    {
                        letterLines[currentLine].end.x = value+1;
                    }
                    onXCoord = false;
                }
                else
                {
                    if(onStartCoord == true)
                    {
                        letterLines[currentLine].start.y = value+1;
                        onStartCoord = false;
                    }
                    else
                    {
                        letterLines[currentLine].end.y = value+1;
                        onStartCoord = true;
                        currentLine++;
                    }
                    onXCoord = true;
                }
            }
            if (character == '\n')
            {
                prevGlyphEnd = static_cast<int>(i) + 1;
                OUTPUT_ERROR(prevGlyphEnd << '\n' << count << '\n');
                break;
            }
        }
        constructFontChar(fontCount,letterLines);
    }

    fontCount++;
    return;
}