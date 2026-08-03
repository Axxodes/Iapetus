#include <iostream>
#include <string>
#include "../libs/math.hpp"
#include <array>
#include "../libs/materialmanager.hpp"
#include "../libs/propertiesclasses.hpp"
#include "../libs/objects.hpp"
#include "../libs/window.hpp"
#include "../libs/services.hpp"

int main()
{
	platform_create_window(1200,720,"Iapetus");

	generateBlankAsset();

	while(running)
	{
		platform_update_window();
	}
	return 0;
}