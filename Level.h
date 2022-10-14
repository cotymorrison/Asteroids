#pragma once

#include "Header.h"
#include "Asteroid.h"
#include "Lights.h"
#include "Shader.h"
#include "Effects.h"
#include "Market.h"
#include "Ship.h"
#include "Hud.h"


class Level
{
private:
	ID3DXSprite*	sprite;
	LPDIRECT3DVERTEXBUFFER9 pSkyBox;
	LPDIRECT3DTEXTURE9 Sky_Texture;
	list<Asteroid>	asteroids;

	Lights			lights;
	Market			market;
	Ship			ship;


	int		level;
	int		score;
	int		lives;

	//World
	D3DXMATRIX		sky_world;
	D3DXMATRIX		sky_scale;
	//Upgrades
	bool* upgrades;
	//level rotion
	D3DXMATRIX level_rot;
	D3DXMATRIX rotation;
	//keyboard variables
	float f_xTranslation;
	float f_yTranslation;
	float f_zTranslation;
	bool b_xTranslation;
	bool b_yTranslation;
	bool b_zTranslation;

	void bubble_sort();

public:
	Level();
	~Level();

	void keyboard();

	void update(D3DXVECTOR3 *ship_vel);
	void renderShip();
	void render();
	void cleanup();

	void CheckBounds();
	void CheckShipBounds();
	list<Asteroid>::iterator Split(list<Asteroid>::iterator &asteroid);

	void Initialize(size_t num_asteroids);

	//Crosshair Information for level rotation
	D3DXMATRIX CheckCrosshairBounds( D3DXVECTOR3 v_Crosshair );

	void setRotation( D3DXMATRIX r );
	//return level rotation
	D3DXMATRIX getLevelRotation();
	
	list<Asteroid>* getAsteroids();
	int getNumAsteroids();

	D3DXMATRIX getWorld();


	int getCurrentLives()
	{	return lives;	}

	int getCurrentScore()
	{	return score;	}

	D3DXMATRIX getShipRotation()
	{	return ship.getRotation();	}

	D3DXVECTOR3 getCrosshairPosition()
	{	return ship.getCrosshairPosition();	}

	bool* getUpgrades()
	{	return market.getUpgrades();	}

	D3DXVECTOR3 getShipVelocity()
	{	return ship.getVelocity();		}

	void setShipVelocity( const D3DXVECTOR3 newVelocity)
	{	ship.setVelocity(newVelocity);	}
};