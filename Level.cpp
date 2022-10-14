#include "Level.h"
#include "Graphics.h"
extern Graphics graphics;

#define iter std::list<Asteroid>::iterator
#define MAX_DISTANCE 36.0f


static const int bound = 500;


Level::Level()
{
	D3DXMatrixIdentity(&sky_world);
	D3DXMatrixScaling(&sky_scale, 500, 500, 500);
	D3DXMatrixIdentity(&level_rot);
	f_xTranslation = f_yTranslation = f_zTranslation = 0;
	b_xTranslation = b_yTranslation = b_zTranslation = false;
	
	level = 0;
	score = 0;
	lives = 3;
}

Level::~Level()
{
	cleanup();
}
//void Level::keyboard()
//{
//
//
//	if( GetKeyState(0x57) & 0x80 ) //W
//	{
//		f_zTranslation = -1.0f;
//		b_zTranslation = true;
//	}
//
//	if( GetKeyState(0x53) & 0x80 ) //S
//	{
//		f_zTranslation = 1.0f;
//		b_zTranslation = true;
//	}
//}

void Level::cleanup()
{
	asteroids.clear();

	SAFE_RELEASE( sprite );
}

bool compare_vectors (D3DXVECTOR3 &first, D3DXVECTOR3 &second)
{
	if (first.x < second.x)
		return true;
	else
		return false;
}

void Level::Initialize(size_t num_asteroids)
{
	ship.LoadModel();
	market.Initialize();


	if(!asteroids.empty())
		asteroids.clear();

	list<D3DXVECTOR3> positions;

	positions.push_back(D3DXVECTOR3(0.0,0.0,0.0));

	while(positions.size() < num_asteroids + 1)
	{
		for(int i=positions.size(); i<num_asteroids+1; i++)
			positions.push_back(bound*D3DXVECTOR3(2*float(rand())/RAND_MAX-1,2*float(rand())/RAND_MAX-1,2*float(rand())/RAND_MAX-1));

		positions.sort(compare_vectors);

		for(list<D3DXVECTOR3>::iterator i=positions.begin(); i!=--positions.end(); i++)
		{
			list<D3DXVECTOR3>::iterator j = i;
			j++;

			for(;j!=--positions.end();)
			{
				list<D3DXVECTOR3>::iterator temp = j++;
				if(abs(temp->x - i->x) < MAX_DISTANCE && abs(temp->y - i->y) < MAX_DISTANCE && abs(temp->z - i->z) < MAX_DISTANCE)
					positions.remove(*temp);
			}
		}
	}
	
	for(list<D3DXVECTOR3>::iterator i=positions.begin(); i!=positions.end(); i++)
		if(i->x == 0.0 && i->y == 0.0 && i->z == 0.0)
		{
			positions.remove(*i);
			break;
		}

	for(list<D3DXVECTOR3>::iterator i = positions.begin(); i!=positions.end(); i++)
		asteroids.push_back(&*i);

	
	//Initialize SkyBox
	Vertex skyVertices[] = 
	{   
	   //Cube vertices repeated image version
		  //Front face (1)
	   {-1.0f,-1.0f,-1.0f, 0.0f, 0.0f, 1.0f, 0xFF000000, 2.0/3, .25},{-1.0f, 1.0f,-1.0f, 0.0f, 0.0f, 1.0f, 0xFF000000, 2.0/3, .5},{ 1.0f, 1.0f,-1.0f, 0.0f, 0.0f, 1.0f, 0xFF000000, 1.0/3, .5},
	   { 1.0f, 1.0f,-1.0f, 0.0f, 0.0f, 1.0f, 0xFF000000, 1.0/3, .5},{ 1.0f,-1.0f,-1.0f, 0.0f, 0.0f, 1.0f, 0xFF000000, 1.0/3, .25},{-1.0f,-1.0f,-1.0f, 0.0f, 0.0f, 1.0f, 0xFF000000, 2.0/3, .25},
		  //Back face (6)
	   { 1.0f,-1.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0xFF000000, 1.0/3, 1.0},{ 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0xFF000000, 1.0/3, .75},{-1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0xFF000000, 2.0/3, .75},
	   {-1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0xFF000000, 2.0/3, .75},{-1.0f,-1.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0xFF000000, 2.0/3., 1.0},{ 1.0f,-1.0f, 1.0f, 0.0f, 0.0f,-1.0f, 0xFF000000, 1.0/3, 1.0},
		  //Bottom face (5)
	   {-1.0f, 1.0f,-1.0f, 0.0f, -1.0f, 0.0f, 0xFF000000, 2.0/3, .5},{-1.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0xFF000000, 2.0/3, .75},{ 1.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0xFF000000, 1.0/3, .75},
	   { 1.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0xFF000000, 1.0/3, .75},{ 1.0f, 1.0f,-1.0f, 0.0f, -1.0f, 0.0f, 0xFF000000, 1.0/3, .5},{-1.0f, 1.0f,-1.0f, 0.0f, -1.0f, 0.0f, 0xFF000000, 2.0/3, .5},
		  //Top face (2)
	   { 1.0f,-1.0f,-1.0f, 0.0f, 1.0f, 0.0f, 0xFF000000, 1.0/3, .25 },{ 1.0f,-1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0xFF000000, 1.0/3, 0},{-1.0f,-1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0xFF000000, 2.0/3, 0},
	   {-1.0f,-1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0xFF000000, 2.0/3, 0},{-1.0f,-1.0f,-1.0f, 0.0f, 1.0f, 0.0f, 0xFF000000, 2.0/3, .25},{ 1.0f,-1.0f,-1.0f, 0.0f, 1.0f, 0.0f, 0xFF000000, 1.0/3, .25},
		  //Right face (4)
	   {-1.0f,-1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0xFF000000, 1.0, .25},{-1.0f, 1.0f, 1.0f,1.0f, 0.0f, 0.0f, 0xFF000000, 1.0, .5},{-1.0f, 1.0f,-1.0f,1.0f, 0.0f, 0.0f, 0xFF000000, 2.0/3, .5},
	   {-1.0f, 1.0f,-1.0f,1.0f, 0.0f, 0.0f, 0xFF000000, 2.0/3, .5},{-1.0f,-1.0f,-1.0f,1.0f, 0.0f, 0.0f, 0xFF000000, 2.0/3, .25},{-1.0f,-1.0f, 1.0f,1.0f, 0.0f, 0.0f, 0xFF000000, 1.0, .25},
		  //Left face (3)
	   { 1.0f,-1.0f,-1.0f,-1.0f, 0.0f, 0.0f, 0xFF000000, 1.0/3, .25},{ 1.0f, 1.0f,-1.0f,-1.0f, 0.0f, 0.0f, 0xFF000000, 1.0/3, .5},{ 1.0f, 1.0f, 1.0f,-1.0f, 0.0f, 0.0f, 0xFF000000, 0, .5},
	   { 1.0f, 1.0f, 1.0f,-1.0f, 0.0f, 0.0f, 0xFF000000, 0, .5},{ 1.0f,-1.0f, 1.0f,-1.0f, 0.0f, 0.0f, 0xFF000000, 0, .25},{ 1.0f,-1.0f,-1.0f,-1.0f, 0.0f, 0.0f, 0xFF000000, 1.0/3, .25}
	};

	pSkyBox = NULL;
	void* sky_vertices;

	graphics.getDevice()->CreateVertexBuffer( sizeof(skyVertices), //size
										D3DUSAGE_WRITEONLY,			//usage
										Vertex::FVF_VERTEX,         //FVF
										D3DPOOL_MANAGED,			//Pool
										&pSkyBox,						//ppVertexBuffer
										NULL);

	pSkyBox->Lock( 0, 0, &sky_vertices, 0 );
	memcpy( sky_vertices, skyVertices, sizeof(skyVertices));
	pSkyBox->Unlock();
	D3DXCreateTextureFromFile( 	graphics.getDevice(), _T("images/StarBox.jpg"), &Sky_Texture );
}

bool compare_asteroids (Asteroid &first, Asteroid &second)
{
	if (first.getPosition().x < second.getPosition().x)
		return true;
	else
		return false;
}

void Level::bubble_sort()
{
	Asteroid temp;
	iter end = asteroids.end();
	end--;

	for(iter i = asteroids.begin(); i != asteroids.end(); i++)
	{
		bool sorted = true;

		for(iter j = end; j != i; j--)
		{
			iter k = j;
			k--;

			if(!compare_asteroids(*k, *j))
			{
				sorted = false;
				temp = *k;
				*k = *j;
				*j = temp;
			}
		}

		if(sorted)
			break;
	}
}

void Level::CheckBounds()
{
	D3DXVECTOR3 norm;
	FLOAT temp;

	bubble_sort();
	//asteroids.sort(compare_asteroids);

	for(iter i=asteroids.begin(); i!=asteroids.end(); i++)
	{
		iter j = i;

		for(j++; j!=asteroids.end(); j++)
		{
			norm = i->getPosition() - j->getPosition();

			if(abs(norm.x) < MAX_DISTANCE)
			{
				temp = D3DXVec3Dot(&norm, &norm);

				if(temp <= (i->getRadius()*i->getRadius() + j->getRadius()*j->getRadius()))
				{
					D3DXVec3Normalize(&norm, &norm);

					D3DXVECTOR3 v1 = i->getVelocity();
					D3DXVECTOR3 v2 = j->getVelocity();
					D3DXVECTOR3 norm_v1 = norm*D3DXVec3Dot(&v1, &norm);
					D3DXVECTOR3 norm_v2 = norm*D3DXVec3Dot(&v2, &norm);
					D3DXVECTOR3 tan_v1 = v1 - norm_v1;
					D3DXVECTOR3 tan_v2 = v2 - norm_v2;
					float m1 = i->getMass();
					float m2 = j->getMass();

					i->setVelocity(&(tan_v1+(norm_v1*(m1 - m2) + 2*m2*norm_v2)/(m1+m2)));
					j->setVelocity(&(tan_v2+(norm_v2*(m2 - m1) + 2*m1*norm_v1)/(m1+m2)));

					i->setAngSpeed(i->getAngSpeed() * -1);
					j->setAngSpeed(j->getAngSpeed() * -1);

					i->updatePos();
					j->updatePos();
				}
			}
			else
				break;
		}
	}
}

void Level::CheckShipBounds()
{
	D3DXVECTOR3 shipVec = ship.getPosition();
	D3DXVECTOR3 astVec;
	FLOAT temp;

	for(iter i=asteroids.begin(); i!=asteroids.end(); i++)
	{
		astVec = i->getPosition();

		astVec -= shipVec;

		temp = D3DXVec3Dot(&astVec, &astVec);

		if(temp < i->getRadius()*i->getRadius() + ship.getRadius()*ship.getRadius())
		{
			//ship collided with asteroid
			lives -= 1;
			//graphics.PlaySound("barrel_roll.wav");
			//check lives
		}
	}
}

list<Asteroid>::iterator Level::Split(list<Asteroid>::iterator &asteroid)
{
	if(asteroid->getScale() > 4.0f)
	{
		float half = asteroid->getScale()/4;
		asteroid->setScale(half);

		D3DXVECTOR3 pos = D3DXVECTOR3(float(rand())/RAND_MAX*half + 2*half, float(rand())/RAND_MAX*half + 2*half, float(rand())/RAND_MAX*half + 2*half);
		
		asteroid->setPosition(&(asteroid->getPosition() + pos));

		asteroids.push_back(Asteroid(*asteroid));

		asteroid->setPosition(&(asteroid->getPosition() - pos));

		asteroids.push_back(Asteroid(*asteroid));
	}

	return asteroids.erase(asteroid);
}

void Level::update(D3DXVECTOR3 *ship_vel)
{
	for(iter i=asteroids.begin(); i!=asteroids.end(); i++)
		i->setVelocity(&(i->getVelocity() + (*ship_vel)));
}

void Level::renderShip()
{
	lights.SetThrusterLight();
	graphics.setLight(lights,0);
	ship.render();
	//market.render();
}

void Level::render()
{
	renderShip();

	//keyboard();
	//Update upgrade list
	upgrades = graphics.getUpgrades();

	//Render SKYLIGHT
	lights.SetSkyLight();
	graphics.setLight(lights, 0);
	graphics.setMaterial();

	//RENDER THE SKYBOX
	graphics.getDevice()->SetRenderState(D3DRS_LIGHTING, TRUE);

	////Check Crosshair boundries for appropriate rotation
	D3DXMATRIX r = CheckCrosshairBounds( graphics.getCrosshairPosition() );
	level_rot = level_rot*r;

	setRotation( r );
	graphics.getDevice()->SetTransform(D3DTS_WORLD, &(sky_scale*level_rot) );
	graphics.getDevice()->SetFVF( Vertex::FVF_VERTEX );
	
	LPDIRECT3DDEVICE9 device = graphics.getDevice();
	device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
	device->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TEXTURE);
	device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);	
	
	device->SetTexture( 0, Sky_Texture );

	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID );

		
	device->SetStreamSource(0, pSkyBox, 0, sizeof(Vertex));
	
	device->DrawPrimitive(D3DPT_TRIANGLELIST, //PrimitiveType
                               0,       //StartVertex
                               12);      //PrimitiveCount

	device->SetTexture( 0, NULL );
	
	graphics.TurnOffLight(0);
	//=============================================================
	//Render Asteroids
	//=============================================================
	//set the ship spotlight before asteroids
	lights.SetPerimeterLight();
	graphics.setLight(lights,0);
	//lights.SetShipViewLight( graphics.getShipRotation() );
	//graphics.setLight(lights,1);
	Asteroid::prerender();


	for(iter i=asteroids.begin(); i!=asteroids.end(); i++)
		i->render(r);
	
	graphics.TurnOffLight(0);
}

D3DXMATRIX Level::getWorld()
{
	return level_rot;
}

//=====================================================================
//Check Crosshair boundries
//Return appropriate rotation
//=====================================================================
D3DXMATRIX Level::CheckCrosshairBounds( D3DXVECTOR3 v_Crosshair )
{
	float yaw, pitch, roll;
	yaw = pitch = roll = 0.0f;

	pitch = ( ( (-v_Crosshair.y/600.0f)+0.5f )* (D3DX_PI/2.0f) )/50.0f;
	yaw = ( ( (-v_Crosshair.x/800.0f)+0.5f )*(D3DX_PI/2.0f) )/50.0f;

	D3DXMATRIX Pitch;
	D3DXMATRIX Yaw;
	D3DXMatrixRotationX(&Pitch,pitch);
	D3DXMatrixRotationY(&Yaw,yaw);
	//D3DXMatrixRotationYawPitchRoll(&tr,yaw,pitch,roll);
	return (Pitch*Yaw);
}
void Level::setRotation( D3DXMATRIX r )
{
	rotation = r;
}
//Get the level Rotation
D3DXMATRIX Level::getLevelRotation()
{
	return rotation;
}
list<Asteroid>* Level::getAsteroids()
{
	return &asteroids;
}

int Level::getNumAsteroids()
{
	return asteroids.size();
}