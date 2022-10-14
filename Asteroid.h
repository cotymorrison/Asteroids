#pragma once

#include "Header.h"


class Asteroid
{
private:
	static DWORD				numMaterials;
	static LPDIRECT3DTEXTURE9	meshTexture;
	static LPDIRECT3DTEXTURE9	bumpTexture;
	static D3DMATERIAL9*		meshMaterials;
	static D3DXMATERIAL*		d3dxMaterials;
	static LPD3DXMESH			mesh;
	
	D3DXMATRIX			world;
	D3DXMATRIX			rotation;
	D3DXMATRIX			m_scale;
	D3DXMATRIX			world_rot;

	D3DXVECTOR3			position;
	D3DXVECTOR3			velocity;
	D3DXVECTOR3			angular;

	float				radius;
	float				ang_speed;
	float				scale;
	float				mass;
	float				speed;

	//For ship movement
	D3DXVECTOR3 Current_Vec;
	float f_xTranslation, f_yTranslation, f_zTranslation;
	bool b_xTranslation, b_yTranslation, b_zTranslation;

public:
	Asteroid();
	Asteroid(D3DXVECTOR3 *pos);
	Asteroid(const Asteroid &copy);
	~Asteroid();
	void cleanup();

	static void prerender();
	void render(const D3DXMATRIX &level_rot);
	void keyboard();
	//void render(D3DXMATRIX level_rot);
	
	void updatePos();

	static void LoadModel();

	D3DXVECTOR3 getPosition();
	void setPosition(const D3DXVECTOR3 *pos);

	D3DXVECTOR3 getVelocity();
	void setVelocity(const D3DXVECTOR3 *vel);

	void setShipVelocity( const D3DXVECTOR3 &newVelocity );
	D3DXVECTOR3 getShipVelocity( );

	D3DXMATRIX getRotation();
	void setRotation(const D3DXMATRIX *rot);

	float getScale();
	void setScale(float scale);
	void setSpeed(float speed);

	float getAngSpeed();
	void setAngSpeed(float speed);

	float getRadius();
	float getMass();

	//D3DXMATRIX CheckCrosshairBounds(  D3DXVECTOR3 v_Crosshair );
};