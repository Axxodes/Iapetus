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
#include "buttonmanager.hpp"

// #include "fontinterpreter.hpp"

#include <fstream>
#include <cmath>

// global vars

static bool running = true;

int updateFPS {20};

HWND textbox;

FrameBuffer Buffer {};

// (global)code stuff

int createdButtonAmount {0};

// functions

void quitApp()
{
	running = false;
}

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
				break;
			}
			else
			{
				Buffer = reAllocFrameBuffer(width*height*sizeof(COLORREF),width,height);
				updateRenderDimensions(width,height);
			} 

			if (!Buffer.memory)
			{
				quitApp();
				break;
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
			int cursorx = GET_X_LPARAM(lParam);
            int cursory = GET_Y_LPARAM(lParam);

			std::cout << "Clicked on: " << cursorx << "," << cursory << std::endl;

			//wanted to note here that the cout autoflush system apparantly doesnt work so i need to manually flush it rn, idk if i turned it off somehow lol
			// ill be including endl in every cout, if theres a fix, please help! (as flushing manually with every cout isnt very optimised)

			createdButtonAmount = syncCurrentButtonCount();

			int foundButton;
			bool didWeFindAButton {false};

			std::vector<Button> returnedButtonArray = returnButtonArray();

			for (int i{0};i<createdButtonAmount;i++)
			{
				Button button = returnedButtonArray[i];
				if (cursorx >= button.x && cursorx < button.x+button.width && cursory >= button.y && cursory < button.y+button.height)
				{
					didWeFindAButton = true;
					foundButton = i;
				}
			}

			if (didWeFindAButton == true)
			{
				Button button = returnedButtonArray[foundButton];
				button.onClick();
			}

    		break;
		}

		case WM_KEYDOWN:
		{
			if (wParam == VK_SHIFT)
			{
				addButton(50,50,50,50,buttonPrint);
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
				  &bitmapInfo,   //info on reading the allocated memory (see line 8 through 15 of the function)
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

	// FrameBuffer setup

	Buffer = createFrameBuffer(width*height*sizeof(COLORREF),width,height);
	
	if (!Buffer.memory)
	{
		// check if the creation failed
		quitApp();
	}

	// quick log so you can see last login time, this was mostly to test fstream

	log();

	auto targetFrameTime = evaluateUpdateFPS(updateFPS);

	// main update loop

	while(running)
	{
		auto start = std::chrono::high_resolution_clock::now();

		platform_update_window();

		if (frameChanged == true)
		{
			std::vector<Button> returnedButtonArray = returnButtonArray();
			createdButtonAmount = syncCurrentButtonCount();

			renderloop(returnedButtonArray,createdButtonAmount);
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