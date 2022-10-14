#pragma once

#include "Header.h"

class DirectInput
{
private:
	LPDIRECTINPUT8 din;    // the pointer to our DirectInput interface
	LPDIRECTINPUTDEVICE8 dinkeyboard;    // the pointer to the keyboard device
	LPDIRECTINPUTDEVICE8 dinmouse;    // the pointer to the mouse device
	BYTE keystate[256];    // the storage for the key-information
	DIMOUSESTATE mousestate;    // the storage for the mouse-information

public:
	// function prototypes
	void initD3D(HWND hWnd);
	void render_frame(void);
	void cleanD3D(void);
	void init_graphics(void);
	void init_light(void);
	void initDInput(HINSTANCE hInstance, HWND hWnd);    // sets up and initializes DirectInput
	void detect_input(void);    // gets the current input data
	void cleanDInput(void);    // closes DirectInput and releases memory

	//return mouse state
	DIMOUSESTATE GetMouseState();
	// the WindowProc function prototype
	//LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};