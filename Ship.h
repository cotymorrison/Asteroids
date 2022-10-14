#pragma once

#include "Header.h"

class Ship
{
private:
	DWORD				numMaterials;
	LPDIRECT3DTEXTURE9	meshTexture;
	LPDIRECT3DTEXTURE9	bumpTexture;
	D3DMATERIAL9*		meshMaterials;
	D3DXMATERIAL*		d3dxMaterials;
	LPD3DXMESH			mesh;

	//Crosshair sprite
	LPDIRECT3DTEXTURE9 pTexture;
	LPD3DXSPRITE hanger;

	D3DXVECTOR3 spritepos;

	D3DXMATRIX		world;
	D3DXMATRIX		rotation;
	
	D3DXMATRIX		translation;
	//Shift ship into proper position
	D3DXVECTOR3		v_Crosshair;		//Vector of where the crosshair is located on screen
	D3DXVECTOR3		Crosshair_Object;

	D3DXVECTOR3		position;
	D3DXVECTOR3		velocity;
	D3DXVECTOR3		cur_rot;
	float			radius;
	float			speed;
	float			scale;


	//keyboard variables
	float xTranslation;
	float yTranslation;
	float zTranslation;
	float xRotation;
	float yRotation;
	float zRotation;


public:
	Ship();
	~Ship();
	void cleanup();
	
	void move();
	void render();
	void keyboard();

	void LoadModel();

	D3DXVECTOR3 getPosition();

	void setPointTo( float x, float y, float z );
	void setPosition(const D3DXVECTOR3 *pos);

	D3DXVECTOR3 getVelocity();
	void setVelocity(const D3DXVECTOR3 vel);

	D3DXVECTOR3 getCrosshairPosition();
	//void setCrosshairPosition();

	D3DXMATRIX getRotation();
	//void getRotation(D3DXMATRIX	*rot);
	void setRotation(const D3DXMATRIX *rot);

	void setTranslation(D3DXMATRIX &tr);
	D3DXMATRIX getTranslation();

	void setScale(float scale);
	void setSpeed(float speed);

	float getRadius();

	void renderBullet();
	void renderShield();
};