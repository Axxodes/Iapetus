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

static HWND window;

//normal includes

#endif

#include <string>

#include "renderer.hpp"
#include "rendererclasses.hpp"

#include <iostream>
#include "framebuffer.hpp"

// #include "fontinterpreter.hpp"

#include <fstream>

// global vars

static bool running = true;

int updateFPS {20};

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
			if (width == 0 || height == 0)
			{
				break;
			}

			if (!Buffer.memory)
			{
				Buffer = createFrameBuffer(width*height*sizeof(COLORREF),width);
				testFillFrameBuffer();
			}
			else
			{
				Buffer = reAllocFrameBuffer(width*height*sizeof(COLORREF),width);
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
				
				Color3 circleCol {};
				circleCol.changeColor(255,255,255);
				Vector2 circleMid {};
				circleMid.changeVector(200,200);
				int radius {320};

				generateCircle(circleMid,radius,circleCol);
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

void log()
{
    time_t timestamp;
    time(&timestamp);
    std::fstream file {};
    file.open("logs.txt");
    if (file.is_open())
    {
        file << ctime(&timestamp);
    }
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
				  &bitmapInfo,   //info on reading the allocated memory (see line 8 through 16 of the function)
				  DIB_RGB_COLORS,//usage
				  SRCCOPY        //i have no idea

	);
	ReleaseDC(window, subwindow);
}

int evaluateUpdateFPS(int updatedFPS)
{
	return (1/updatedFPS)*1000;
}

void initialise_window(int x, int y)
{
    platform_create_window(x,y,"Iapetus");
	HWND window = GetActiveWindow();

	RECT rect;
	GetClientRect(window, &rect);

	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	Buffer = createFrameBuffer(width*height*sizeof(COLORREF),width);
	testFillFrameBuffer();

	log();

	int fps = evaluateUpdateFPS(updateFPS);

	while(running)
	{
		platform_update_window();
		displayBuffer(window,Buffer);
		Sleep(updateFPS);
	}
	std::free(Buffer.memory);
}