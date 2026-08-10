// NO shoutout to spiderbat229
#pragma once

#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#ifndef NOMINMAX
#define NOMINMAX
#endif

#include <windows.h>
#endif

#include <string>

#include "renderer.hpp"
#include "rendererclasses.hpp"

static HWND window;
static bool running = true;

HWND textbox;

#include <iostream>

LRESULT CALLBACK windows_window_callback(HWND window, UINT msg,
										 WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;
	switch(msg)
	{
		case WM_CREATE:
		{
			break;
		}

		case WM_CLOSE:
		{
			running = false;
			break;
		}

		case WM_KEYDOWN:
		{
			if(wParam == VK_SHIFT)
			{
				HDC subwindow = GetDC(window);
				Color3 color {};
				color.changeColor(0,0,0);
				Vector2 vec1 {};
				vec1.changeVector(50,50);
				Vector2 vec2 {};
				vec2.changeVector(65,65);
				drawLine(subwindow,vec1,vec2,color);
			} 
			break;
		}

		default:
		{
			// windows default input
			result = DefWindowProcA(window,msg,wParam,lParam);
		}
	}
	return result;
}
bool platform_create_window(int width, int height, const char* title)
{
	HINSTANCE instance = GetModuleHandleA(0);

	WNDCLASSA wc = {};
	wc.hInstance = instance;
	wc.hIcon = (HICON)LoadImage(instance,"icon.ico",IMAGE_ICON,32,32,LR_LOADFROMFILE);
	wc.hCursor = LoadCursor(NULL,IDC_ARROW); // default twin
	wc.lpszClassName = title; // not the title
	wc.lpfnWndProc = windows_window_callback;

	if (!RegisterClassA(&wc))
	{
		return false;
	}

	// WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX
	int dwStyle = WS_OVERLAPPEDWINDOW;

	window = CreateWindowExA(0, title, // reference lpszClassName
								  title, // real title
								  dwStyle,
								  100, //position x
								  100, // position y
								  width,
								  height,
								  NULL, //parent
								  NULL, // MENU
								  instance,
								  NULL); // lpParam

	if(window == NULL)
	{
		return false;
	}

	ShowWindow(window,SW_SHOW);

	return true;
}

void platform_update_window()
{
	MSG msg;

	while(PeekMessageA(&msg, window,0,0,PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessageA(&msg);
	}
}

void initialise_window(int x, int y)
{
    platform_create_window(x,y,"Iapetus");

	while(running)
	{
		platform_update_window();
	}
}