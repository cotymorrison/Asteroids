#pragma once

#define DIRECTINPUT_VERSION 0x0800

#pragma comment( lib, "winmm.lib" )
#pragma comment( lib, "D3dx9.lib" )
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")

//windows and directx
#include <Windows.h>
#include <mmsystem.h>
#include <d3dx9.h>
#include <d3dx9tex.h>
#include <D3dx9core.h>
#include <dinput.h>

//common header files
#include <list>
#include <cmath>
#include <random>
#include <string>
#include <tchar.h>
#include <sstream>
#include <strsafe.h>
#include <iostream>
#include <vector>
#include <list>

//sound header files
#include <shellapi.h>
#include <xaudio2.h>
#include <conio.h>

using namespace std;

#pragma warning( disable : 4996 ) // disable deprecated warning 
#pragma warning( disable : 4305 ) // disable double to float warning 
#pragma warning( default : 4996 )

// define the screen resolution and keyboard macros
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 1024

#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }
#define SAFE_DELETE(p)       { if (p) { delete (p);    (p)=NULL; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }

using namespace std;

enum
{
	//Shield Upgrades:
		//Shield Boost Amplifier I
		SHIELD_AMP = 0,
		//5A Prototype Shield Support
		SHIELD_PROTO = 1,
	//Generator Upgrades:
		//Type-D Power Core Modification
		GEN_TYPED = 2,
		//Type-E Power Core Modification
		GEN_TYPEE = 3,
	//Cannon Upgrades:
		//75mm Gatling Rail I
		GUN_GATLIN = 4,
		//75mm Prototype I Gauss Gun
		GUN_PROTO = 5,
		//Partial Weapon Navigation
		GUN_POINT = 6,
	//Thruster Upgrades:
		//Type-D Altered SS Overdrive
		THRUSTER_TYPED = 7,
		//Mark I Modified SS Inertial Stabilizers
		THRUSTER_MARKI = 8
};