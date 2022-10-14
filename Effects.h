#pragma once

#include "Header.h"
#include "Lights.h"
#include "Sound.h"

struct Laser
{
	Sound		sound;
	D3DXVECTOR3 position;
	D3DXVECTOR3 direction;
	int			magnitude;
	Laser( D3DXMATRIX rot );	//init function
};
struct SpotLight
{
	D3DXVECTOR3 position;
	D3DXVECTOR3 direction;
};

class Effects
{
private:
	//Lights
	Lights					light;
	D3DXVECTOR3				light_position;
	D3DXVECTOR3				light_direction;
	SpotLight				spotlight;

	//Mesh Shield
	static DWORD				numMaterials;
	static LPDIRECT3DTEXTURE9	meshTexture;
	static D3DMATERIAL9*		meshMaterials;
	static D3DXMATERIAL*		d3dxMaterials;
	static LPD3DXMESH			mesh;
	static D3DXMATRIX			start_pos;
	//Bullet sprite
	LPDIRECT3DTEXTURE9		Bullet_Texture;
	LPD3DXSPRITE			Bullet;
	//Shield sprite
	LPDIRECT3DTEXTURE9		Shield_Texture;
	LPD3DXSPRITE			Shield;
	float					shield_energy;
	//Thrust sprite
	LPDIRECT3DTEXTURE9		Thrust_Texture;
	LPD3DXSPRITE			Thrust;
	LPDIRECT3DTEXTURE9		AuxThrustR_U30_Texture;
	LPDIRECT3DTEXTURE9		AuxThrustR_D30_Texture;
	LPD3DXSPRITE			AuxThrustRD;
	LPD3DXSPRITE			AuxThrustRU;
	LPDIRECT3DTEXTURE9		AuxThrustL_U30_Texture;
	LPDIRECT3DTEXTURE9		AuxThrustL_D30_Texture;
	LPD3DXSPRITE			AuxThrustLD;
	LPD3DXSPRITE			AuxThrustLU;
	//Only 20 bullets allowed
	Laser*					laser;
	list<Laser>				laser_list;
	int						laser_count;
	bool*					open;
	
	//Energy
	float					energy_charge_rate;
	float					thruster_drain_rate;



public:
	Effects();
	~Effects();

	void set();
	void cleanup();
	void Initialize();

	float getThrusterDrainRate();

	void render();
	void renderBullet( D3DXVECTOR3 position );
	
	void renderShield();
	void rotateShieldLight();
	void setShieldEnergyUse( float energy );
	void UpgradeToShieldProto();

	void renderThruster();
	void renderAuxThrusterRight();
	void renderAuxThrusterLeft();

	int checkBulletBounds();
	D3DXMATRIX CheckCrosshairBounds( D3DXVECTOR3 v_Crosshair );

	D3DXVECTOR3 GetSpotLightPosition();
	D3DXVECTOR3 GetSpotLightDirection();

	void UpgradeToGenTypeD();
	void UpgradeToGenTypeE();
	void UpgradeToGunGatlin();
	void UpgradeToGunProto();
	void UpgradeToGunPoint();
	void UpgradeToThrusterTypeD();
	void UpgradeToThrusterMarkI();
};