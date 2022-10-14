#pragma once

#include "Header.h"

#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }


class Lights
{
private:	
	D3DLIGHT9	light;
    //D3DLIGHT9 skylight;
	D3DLIGHT9 shiplight;
	D3DLIGHT9 spotlight;
	D3DLIGHT9	shieldlight;

public:
	Lights();
	void SetSkyLight();
	void SetShieldLight( D3DXVECTOR3 light_position, D3DXVECTOR3 light_direction  );
	void SetThrusterLight();
	void SetShipViewLight( D3DXMATRIX ship_rot );
	void SetPerimeterLight();
	D3DLIGHT9 getLight();
};