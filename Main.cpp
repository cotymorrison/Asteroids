#include "Graphics.h"
#include "DirectInput.h"
//--------------------------------------------------------------------
//Additional Library Directories
#include "Effects.h"
#include "Asteroid.h"
#include "Level.h"
#include "Ship.h"
#include "Lights.h"
#include "Sound.h"
//--------------------------------------------------------------------
using namespace std;


#ifdef  UNICODE  
    #define cin wcin
    #define cout wcout
    #define string wstring
	#define ifstream wifstream
	#define ofstream wofstream
#endif

Graphics		graphics;
DirectInput		mouse;


LPDIRECT3DVERTEXBUFFER9 pVB;
LPDIRECT3DTEXTURE9 pTexture;
float xRotation, yRotation, zRotation;
float xTranslation, yTranslation, zTranslation;
bool wireframe;




//-----------------------------------------------------------------------------
// Name: MsgProc()
// Desc: The window's message handler
//-----------------------------------------------------------------------------
LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch( msg )
    {
        case WM_DESTROY:
			graphics.cleanup();
            PostQuitMessage( 0 );
            return 0;
		/*case WM_GRAPHNOTIFY:
			sound.HandleEvent();
			PostQuitMessage( 0 );
			return 0;*/
    }

    return DefWindowProc( hWnd, msg, wParam, lParam );
}


void keyboard( )
{
	if( GetKeyState(0x41) & 0x80 ) //A
		xTranslation -= 0.01;

	if( GetKeyState(0x44) & 0x80 ) //D
		xTranslation += 0.01;

	if( GetKeyState(0x57) & 0x80 ) //W
		yTranslation += 0.01;

	if( GetKeyState(0x53) & 0x80 ) //S
		yTranslation -= 0.01;

	if( GetKeyState(0x5A) & 0x80 ) //Z
		zTranslation -= 0.01;

	if( GetKeyState(0x58) & 0x80 ) //X
		zTranslation += 0.01;


	if( GetKeyState(0x4A) & 0x80 ) //J
		xRotation -= 0.01;

	if( GetKeyState(0x4C) & 0x80 ) //L
		xRotation += 0.01;

	if( GetKeyState(0x49) & 0x80 ) //I
		yRotation += 0.01;

	if( GetKeyState(0x4B) & 0x80 ) //K
		yRotation -= 0.01;

	if( GetKeyState(0x4D) & 0x80 ) //Z
		zRotation -= 0.01;

	if( GetKeyState(VK_OEM_COMMA) & 0x80 ) //X
		zRotation += 0.01;

	SHORT state = GetAsyncKeyState (VK_RETURN);

	if(  state &&  state & 1  )
		wireframe = !wireframe;
}

void render()
{
	graphics.beginScene();
	//graphics.displayFPS();

	//graphics.setLight();

	graphics.render();

	graphics.endScene();
}

//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: The application's entry point
//-----------------------------------------------------------------------------
INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR, INT )
{
    UNREFERENCED_PARAMETER( hInst );

    // Register the window class
    WNDCLASSEX wc =
    {
        sizeof( WNDCLASSEX ), CS_CLASSDC, MsgProc, 0L, 0L,
        GetModuleHandle( NULL ), NULL, NULL, NULL, NULL,
        _T("Asteroids!"), NULL
    };
    RegisterClassEx( &wc );

	RECT rect;

	rect.top = rect.left = 0;
	rect.right = 800;
	rect.bottom = 600;

	//AdjustWindowRect( &rect, WS_OVERLAPPEDWINDOW, FALSE );

    // Create the application's window
    HWND hWnd = CreateWindow( _T("Asteroids!"), _T("Asteroids!"),
		WS_EX_TOPMOST | WS_POPUP, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT,
                              NULL, NULL, wc.hInstance, NULL );
   
    // Initialize Direct3D
	if( SUCCEEDED( graphics.initialize( hInst, hWnd ) ) )
    {
		//Set up DirectInput
		mouse.initDInput(hInst, hWnd);    // initialize DirectInput

		graphics.setCamera(0,10,-80);
		graphics.setProjection( 800, 600 );
		//graphics.setLight();
		graphics.setMaterial();
	      
        // Show the window
        ShowWindow( hWnd, SW_SHOWDEFAULT );
        UpdateWindow( hWnd );

        // Enter the message loop
        MSG msg;
        ZeroMemory( &msg, sizeof( msg ) );		
           
        while( msg.message != WM_QUIT )
        {
            if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
            {
                TranslateMessage( &msg );
                DispatchMessage( &msg );
				UpdateWindow( hWnd );
            }
            else
            {
				//keyboard();				
				render();
				//sound.PlayFile();
            }
        }        
    }

    UnregisterClass( _T("Asteroids!"), wc.hInstance );
    return 0;
}



