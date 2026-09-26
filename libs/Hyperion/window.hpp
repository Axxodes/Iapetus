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
#include <windowsx.h>

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

int savedCursorX {};
int savedCursorY {};

Vector2 savedCursorVector2 {};

bool firstSelection {true};

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
				Buffer = createFrameBuffer(width*height*sizeof(COLORREF),width,height);
				updateRenderDimensions(width,height);
			}
			else
			{
				Buffer = reAllocFrameBuffer(width*height*sizeof(COLORREF),width,height);
				updateRenderDimensions(width,height);
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

		case WM_LBUTTONDOWN:
		{
    		std::cout << "Left mouse button pressed\n";

			int cursorx = GET_X_LPARAM(lParam);
			int cursory = GET_Y_LPARAM(lParam);

			Color3 testColor {};
			testColor.changeColor(255,255,255);

			Vector2 currentCursorVector2 {};
			currentCursorVector2.changeVector(cursorx,cursory);

			if (firstSelection==true)
			{
				savedCursorX = cursorx;
				savedCursorY = cursory;

				savedCursorVector2.changeVector(cursorx,cursory);

				firstSelection = false;

				break;
			}
			else 
			{
				drawLine(savedCursorVector2,currentCursorVector2,testColor);
				firstSelection = true;
			}

    		break;
		}

		case WM_KEYDOWN:
		{
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
	wc.hIcon = (HICON)LoadImage(instance,"icon.ico",IMAGE_ICON,32,29,LR_LOADFROMFILE);
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

std::chrono::microseconds evaluateUpdateFPS(int updatedFPS)
{
	return std::chrono::microseconds(1000000/updatedFPS);
}

void initialise_window(int x, int y)
{
    platform_create_window(x,y,"Iapetus");
	HWND window = GetActiveWindow();

	RECT rect;
	GetClientRect(window, &rect);

	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	Buffer = createFrameBuffer(width*height*sizeof(COLORREF),width,height);
	testFillFrameBuffer();

	log();

	auto targetFrameTime = evaluateUpdateFPS(updateFPS);

	while(running)
	{
		auto start = std::chrono::high_resolution_clock::now();

		platform_update_window();

		if (frameChanged == true)
		{
			displayBuffer(window,Buffer);
			frameChanged = false;
		}

		auto end = std::chrono::high_resolution_clock::now();

    	auto duration = duration_cast<std::chrono::microseconds>(end - start);

		if (duration < targetFrameTime)
		{
			std::this_thread::sleep_for(targetFrameTime - duration);
		}
	}
	std::free(Buffer.memory);
}