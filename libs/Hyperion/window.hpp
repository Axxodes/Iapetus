#pragma once

//win32 include

#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#ifndef NOMINMAX
#define NOMINMAX
#endif

#include <windows.h>

//normal includes

#endif

#include <string>

#include "renderer.hpp"
#include "rendererclasses.hpp"

#include <iostream>
#include "framebuffer.hpp"

// global vars

static HWND window;
static bool running = true;

HWND textbox;

FrameBuffer Buffer {};

// code

LRESULT CALLBACK windows_window_callback(HWND window, UINT msg,
										 WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;
	switch(msg)
	{
		case WM_SIZE:
		{
			int width = LOWORD(lParam);
			int height = HIWORD(lParam);

			if (!Buffer.memory)
			{
				Buffer = createFrameBuffer(width*height*4,width);
				testFillFrameBuffer();
			}
			else
			{
				std::free(Buffer.memory);
				
				Buffer = createFrameBuffer(width*height*4,width);
				testFillFrameBuffer();
			}
			break;
		}

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
				
				Vector2 vec {};
				vec.changeVector(65,65);
				Color3 col {};
				col.changeColor(255,255,255);
				changePixel(vec,col);
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

void displayBuffer(HWND window, FrameBuffer fa)
{
	HDC subwindow = GetDC(window);
	RECT rect;
	GetClientRect(window, &rect);

	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	BITMAPINFO bitmapInfo{};

	bitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitmapInfo.bmiHeader.biWidth = width;
	bitmapInfo.bmiHeader.biHeight = -height;
	bitmapInfo.bmiHeader.biPlanes = 1;
	bitmapInfo.bmiHeader.biBitCount = 32;
	bitmapInfo.bmiHeader.biCompression = BI_RGB;
	StretchDIBits(subwindow, // reference to hdc
				  0,        	 // xdest
				  0,        	 // ydest
				  width,
				  height,
				  0,
				  0,
				  width,
				  height,
				  fa.memory,	 //reference to the allocated memory
				  &bitmapInfo,   //info on reading the allocated memory (see line 7 through 14 of the function)
				  DIB_RGB_COLORS,//usage
				  SRCCOPY        //i have no idea

	);
	ReleaseDC(window, subwindow);
}

void initialise_window(int x, int y)
{
    platform_create_window(x,y,"Iapetus");
	HWND window = GetActiveWindow();

	RECT rect;
	GetClientRect(window, &rect);

	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	Buffer = createFrameBuffer(width*height*4,width);
	testFillFrameBuffer();

	while(running)
	{
		platform_update_window();
		displayBuffer(window,Buffer);
		Sleep(50);
	}
	std::free(Buffer.memory);
}