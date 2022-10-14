#pragma once

#include "Header.h"

class Market
{
private:
	bool* upgrades;
	int* dollars;			//cost of upgrades
	int money;

	LPDIRECT3DTEXTURE9 pTexture;
	LPD3DXSPRITE hanger;

public:
	ID3DXFont				*p_font_title;
	ID3DXFont				*p_font_subtitle;
	ID3DXFont				*p_font_price;
	ID3DXFont				*p_font_text;
	ID3DXFont				*p_font_player;

	Market();
	~Market();
	void cleanup();
	void render();
	
	bool* getUpgrades();
	int GetMoney();
	int* GetDollars();

	void SetMoney( int dollar );

	void keyboard();
	void Initialize();
	void setUpgrades();

//Shield Upgrades:
	//Shield Boost Amplifier I
	void setShieldAmp();
	//5A Prototype Shield Support
	void ShieldProto();
//Generator Upgrades:
	//Type-D Power Core Modification
	void setGenTypeD();
	//Type-E Power Core Modification
	void setGenTypeE();
//Cannon Upgrades:
	//75mm Gatling Rail I
	void setGunGatlin();
	//75mm Prototype I Gauss Gun
	void setGunProto();
	//Partial Weapon Navigation
	void setGunPoint();
//Thruster Upgrades:
	//Type-D Altered SS Overdrive
	void setThrusterTypeD();
	//Mark I Modified SS Inertial Stabilizers
	void setThrusterMarkI();
};