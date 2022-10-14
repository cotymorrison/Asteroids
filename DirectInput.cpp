#include "Graphics.h"
#include "DirectInput.h"

extern Graphics graphics;

// this is the function that initializes DirectInput
void DirectInput::initDInput(HINSTANCE hInstance, HWND hWnd)
{
    // create the DirectInput interface
    DirectInput8Create(hInstance,    // the handle to the application
                       DIRECTINPUT_VERSION,    // the compatible version
                       IID_IDirectInput8,    // the DirectInput interface version
                       (void**)&din,    // the pointer to the interface
                       NULL);    // COM stuff, so we'll set it to NULL

    // create the devices
    din->CreateDevice(GUID_SysKeyboard,    // the default keyboard ID being used
                      &dinkeyboard,    // the pointer to the device interface
                      NULL);    // COM stuff, so we'll set it to NULL
    din->CreateDevice(GUID_SysMouse,
                      &dinmouse,
                      NULL);

    // set the data formats
    dinkeyboard->SetDataFormat(&c_dfDIKeyboard);
    dinmouse->SetDataFormat(&c_dfDIMouse);

    // set the control you will have over the devices
    dinkeyboard->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
    dinmouse->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND);
}
// this is the function that gets the latest input data
void DirectInput::detect_input(void)
{
    // get access if we don't have it already
    dinkeyboard->Acquire();
    dinmouse->Acquire();

    // get the input data
    dinkeyboard->GetDeviceState(256, (LPVOID)keystate);
    dinmouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&mousestate);
}
// this is the function that closes DirectInput
void DirectInput::cleanDInput(void)
{
    dinkeyboard->Unacquire();    // make sure the keyboard is unacquired
    dinmouse->Unacquire();    // make sure the mouse in unacquired
    din->Release();    // cl ose DirectInput before exiting
}
DIMOUSESTATE DirectInput::GetMouseState()
{
	return mousestate;
}