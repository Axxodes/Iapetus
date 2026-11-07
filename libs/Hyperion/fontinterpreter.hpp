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

struct Curve
{
    Vector2 start;
    Vector2 end;
    Vector2 anchor;
};

struct Character
{
    uint8_t fontId {};
    std::vector<Line> lines;
    std::vector<Curve> curves;

    void drawCharToScreen(int size, Vector2 origin)
    {
        int vectorSize = static_cast<int>(lines.size());
        for(int i{0};i<vectorSize;i++)
        {
            bresenhamLineDraw((lines[i].start.x*size+origin.x),(lines[i].start.y*size+origin.y),(lines[i].end.x*size+origin.x),(lines[i].end.y*size+origin.y),Color3{255,255,255});
        }
        int vector2Size = static_cast<int>(curves.size());
        for(int i{0};i<vector2Size;i++)
        {
            drawBezierCurve(curves[i].start*size+origin,curves[i].end*size+origin,curves[i].anchor*size+origin,10*size);
        }
    }
};

struct Font
{
    std::vector<Character> characters;
};

void drawText(Vector2 origin,Font* font,int fontSize,const char* text)
{
    bool doneParsing{false};
    int currentLetter{0};
    while(doneParsing==false)
    {
        char character = text[currentLetter];
        if(!character)
        {
            doneParsing=true;
            continue;
        }
        int value = character - 'A';
        font->characters[value].drawCharToScreen(fontSize,Vector2(origin.x+((4*fontSize)*currentLetter),origin.y));
        currentLetter++;
    }
}

void drawAllFontChars(Vector2 origin,Font* font,int fontSize)
{
    for(size_t i{0};i<font->characters.size();i++)
    {
        font->characters[i].drawCharToScreen(fontSize,Vector2(origin.x+((4*fontSize)*i),origin.y/*+(13*static_cast<int>(i/10))*/));
    }
}

void constructFontChar(int fontId,std::vector<Line> lines,std::vector<Curve> curves,Font* font)
{
    Character character {};
    character.lines = lines;
    character.curves = curves;
    character.fontId = fontId;

    font->characters.push_back(character);
}

void openFont(const wchar_t* name, Font* font)
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
        int totalLines {0};
        int totalThings {0};
        int totalCurves {0};

        for(size_t i{0};i<fileBuffer.used;i++)
        {
            if(static_cast<int>(i)<prevGlyphEnd)
            {
                continue;
            }
            char letter = static_cast<char>(fileBuffer.memory[i]);
            if(letter == ';')
            {
                totalThings++;
            }
            if(letter == 'b')
            {
                totalCurves++;
            }
            if(letter == '\n')
            {
                break;
            }
        }

        totalLines = totalThings-totalCurves;

        std::vector<Line> letterLines(totalLines);
        std::vector<Curve> letterCurves(totalCurves);

        bool onXCoord {true};
        bool onStartCoord {true};
        int curveStage{0}; //if 0, there isnt a curve

        int currentLine {0};
        int currentCurve {0};

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
                    if(curveStage==0)
                    {
                        if(onStartCoord == true)
                        {
                            letterLines[currentLine].start.x = value+1;
                        }
                        else
                        {
                            letterLines[currentLine].end.x = value+1;
                        }
                    }
                    else
                    {
                        if(curveStage==1)
                        {
                            letterCurves[currentCurve].start.x = value+1;
                        }
                        if(curveStage==2)
                        {
                            letterCurves[currentCurve].end.x = value+1;
                        }
                        if(curveStage==3)
                        {
                            letterCurves[currentCurve].anchor.x = value+1;
                        }
                    }
                    onXCoord = false;
                }
                else
                {
                    if(curveStage==0)
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
                    }
                    else
                    {
                        if(curveStage==1)
                        {
                            letterCurves[currentCurve].start.y = value+1;
                        }
                        if(curveStage==2)
                        {
                            letterCurves[currentCurve].end.y = value+1;       
                        }
                        if(curveStage==3)
                        {
                            letterCurves[currentCurve].anchor.y = value+1;
                            curveStage=0;
                            onXCoord = true;
                            currentCurve++;
                            continue;
                        }
                        curveStage++;
                    }
                    onXCoord = true;
                }

                continue;
            }
            if (character == 'b')
            {
                curveStage = 1;
            }

            if (character == '\n')
            {
                prevGlyphEnd = static_cast<int>(i) + 1;
                OUTPUT_ERROR(prevGlyphEnd << '\n' << count << '\n');
                break;
            }
        }
        constructFontChar(fontCount,letterLines,letterCurves,font);
    }

    fontCount++;
    return;
}