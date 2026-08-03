#pragma once

#include "math.hpp"
#include "objects.hpp"
#include "propertiesclasses.hpp"
#include "window.hpp"
#include <windows.h>

void initialise_window(int x, int y)
{
    platform_create_window(x,y,"Iapetus");

	while(running)
	{
		platform_update_window();
	}
}

/*bool start_renderer()
{
    
} */