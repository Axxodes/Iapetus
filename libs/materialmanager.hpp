#pragma once
#include <string>
#include <array>

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