#pragma once

#include "Header.h"
#include "Lights.h"
#include "Sound.h"
#include "Level.h"
#include "Shader.h"
#include "Effects.h"
#include "Hud.h"
#include "Market.h"




struct SimpleVertex
{
    float x, y, z;
    DWORD color;
	enum{ FVF_VERTEX = D3DFVF_XYZ | D3DFVF_DIFFUSE };
};

struct Vertex
{
    float x, y, z;
	D3DVECTOR normal;
    DWORD color;
	float u, v;
	enum{ FVF_VERTEX = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1 };
};


class Graphics
{
private:
    LPDIRECT3D9             pD3D;		// Used to create the D3DDevice
    LPDIRECT3DDEVICE9       pDevice;	// Rendering device        
    D3DPRESENT_PARAMETERS   d3dpp;
	ID3DXFont*				font;

	D3DXMATRIX				world;

	//Camera
    D3DXMATRIX				view;			//camera view
	D3DXMATRIX				projection;		//camera projection
	D3DXVECTOR3				camPos;

	//Effects
	//Lights					lights;
	Sound					sound;

	//Game
	//User					user;
	Level					level;
	Shader					shader;
	Effects					effect;
	Hud						hud;
	//Market					market;

	//Time
	DWORD					time;
	DWORD					last;

public:
    Graphics();
    HRESULT initialize( HINSTANCE hInst, HWND hWnd );
    void cleanup();

    LPDIRECT3DDEVICE9 getDevice();

	//Get Ship information for level
	D3DXMATRIX getShipRotation();
	D3DXVECTOR3 getCrosshairPosition();
	D3DXVECTOR3 getShipVelocity();
	void setShipVelocity( const D3DXVECTOR3 newVelocity);


	void updateWorld();
	void setCamera(float x, float y, float z);
	void setProjection(int width, int height);
	D3DXVECTOR3 getCamPos();
	D3DXMATRIX GetView();
    
	void setLight(Lights light, int pos);
	void TurnOffLight(int pos);
	void setMaterial();
	bool* getUpgrades();

	void PlaySound(LPSTR szFilename);

	float getTimeDifference();
	float getFPS();
	void displayFPS();

	D3DXVECTOR3 getLightVector();
	D3DXMATRIX getView();
	D3DXMATRIX getProj();

	void ShadeSpec(D3DXMATRIX *Model, LPD3DXMESH mesh, LPDIRECT3DTEXTURE9 texture, DWORD numMaterials);
	void ShadeBump(D3DXMATRIX *Model, D3DMATERIAL9 material, LPD3DXMESH mesh, LPDIRECT3DTEXTURE9 texture, LPDIRECT3DTEXTURE9 bump_map, DWORD numMaterials);



	HRESULT beginScene();
	void render();
    HRESULT endScene(); 

	void LEVEL_USER_update();
	//==============================================
	//Level Linkage
	//==============================================
	D3DXMATRIX LEVEL_getLevelRotation();
	list<Asteroid>* LEVEL_getAsteroids();
	list<Asteroid>::iterator LEVEL_Split(list<Asteroid>::iterator &it);
	//==============================================
	//Hud Linkage
	//==============================================
	bool HUD_EnergyStateMax();
	bool HUD_EnergyStateMin();

	void HUD_AdjustEnergyLevel( const float consumption );

	bool HUD_ShieldState();
	bool HUD_EnergyShieldStateMin();
	void HUD_SetShieldUse( bool use );

	void HUD_UpgradeToGenTypeD();
	void HUD_UpgradeToGenTypeE();
	//==============================================
	//User Linkage
	//==============================================
	int USER_getCurrentLives();
	int USER_getCurrentScore();
	//==============================================
	//Effects Linkage
	//==============================================
	void EFFECTS_UpgradeToShieldProto();
	void EFFECTS_UpgradeToGenTypeD();
	void EFFECTS_UpgradeToGenTypeE();
	void EFFECTS_UpgradeToGunGatlin();
	void EFFECTS_UpgradeToGunProto();
	void EFFECTS_UpgradeToGunPoint();
	void EFFECTS_UpgradeToThrusterTypeD();
	void EFFECTS_UpgradeToThrusterMarkI();
	//=======================
	float EFFECTS_getThrusterDrainRate();
	void  EFFECTS_renderAuxThrusterRight();
	void  EFFECTS_renderAuxThrusterLeft();
	void  EFFECTS_renderThruster();
};