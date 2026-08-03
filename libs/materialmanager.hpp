#pragma once
#include <string>
#include <array>
#include <fstream>
#include <iostream>

class material 
{
	public:
	std::string name {};
	bool usesAsset {false};

	void rename(std::string newName)
	{
		name = newName;
	}
	void switchMethod()
	{
		if (usesAsset == true)
		{
			usesAsset = false;
		}
		else 
		{
			usesAsset = true;
		}
	}
};

void generateBlankAsset()
{
    // make it a .png or wtv we use later lol 

    std::ofstream file {};
    file.open("Asset.txt");
    if (file.is_open())
    {
        file << "NO SHOUTOUT TO SPIDER";
        file.close();
    }
}