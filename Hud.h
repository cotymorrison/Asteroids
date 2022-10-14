#pragma once
#include "Header.h"

struct EnergyBar
{
	//Energy sprite
	LPDIRECT3DTEXTURE9		Meter_Texture;
	LPD3DXSPRITE			Meter;
	D3DXMATRIX				Meter_scale;
	LPDIRECT3DTEXTURE9		Energy_Texture;
	LPD3DXSPRITE			Energy;
	D3DXMATRIX				Energy_scale;
	float					s;
};

class Hud
{
private:
	EnergyBar				energy_bar;
	float					cur_energy;		//100% initial
	float					energy_cap;
	bool					shielduse;		//true if can use shield
	//Clone
	LPDIRECT3DTEXTURE9		Clone_Texture;
	LPD3DXSPRITE			Clone;
	D3DXMATRIX				Clone_scale;
public:
	ID3DXFont				*p_font_Words;
	ID3DXFont				*p_font_Numbers;

	Hud();
	void Initialize();
	void EnergyBarInit();
	void render();

	//Shield
	void SetShieldUse( bool use );
	bool ShieldState();
	bool EnergyShieldStateMin();

	//Energy
	bool EnergyStateMin();
	bool EnergyStateMax();
	void AdjustEnergyLevel( float consumption );
	void UpgradeToGenTypeD();
	void UpgradeToGenTypeE();
};