#include "Asteroid.h"
#include "Graphics.h"
extern Graphics graphics;

DWORD					Asteroid::numMaterials = NULL;
LPDIRECT3DTEXTURE9		Asteroid::meshTexture = NULL;
LPDIRECT3DTEXTURE9		Asteroid::bumpTexture = NULL;
D3DMATERIAL9*			Asteroid::meshMaterials = NULL;
D3DXMATERIAL*			Asteroid::d3dxMaterials = NULL;
LPD3DXMESH				Asteroid::mesh = NULL;


static const int bound = 500;


Asteroid::Asteroid()
{
	//position = D3DXVECTOR3(401*float(rand())/RAND_MAX - 200, 401*float(rand())/RAND_MAX - 200, 401*float(rand())/RAND_MAX - 200);
	//velocity = D3DXVECTOR3(0,0,0);
	//speed = 0.0f;
	//scale = pow(2.0, (rand()%3 + 1))*4.0f;
	//D3DXMatrixScaling(&m_scale, scale, scale, scale);

	//D3DXMatrixIdentity(&rotation);
	//D3DXMatrixIdentity(&world);
	//D3DXMatrixIdentity(&world_rot);

	//For ship movement
	//Current_Vec = D3DXVECTOR3(0,0,0);
	//f_xTranslation = f_yTranslation = f_zTranslation = 0;
	//b_xTranslation = b_yTranslation = b_zTranslation = false;
}
Asteroid::Asteroid(D3DXVECTOR3 *pos)
{
	//If there is no mesh, load it
	if(mesh == NULL)
		this->LoadModel();

	//Compute a bounding sphere for the mesh
	D3DXVECTOR3* pData;
    D3DXVECTOR3 vCenter;
    mesh->LockVertexBuffer( 0, ( LPVOID* )&pData );
    D3DXComputeBoundingSphere( pData, mesh->GetNumVertices(), D3DXGetFVFVertexSize( mesh->GetFVF() ), &vCenter, &radius );
    mesh->UnlockVertexBuffer();

	position = *pos;
	velocity = D3DXVECTOR3(2*float(rand())/RAND_MAX - 1, 2*float(rand())/RAND_MAX - 1, 2*float(rand())/RAND_MAX - 1);
	angular = D3DXVECTOR3(2*float(rand())/RAND_MAX - 1, 2*float(rand())/RAND_MAX - 1, 2*float(rand())/RAND_MAX - 1);
	D3DXVec3Normalize(&velocity, &velocity);
	D3DXVec3Normalize(&angular, &angular);

	float speed = 25*float(rand())/RAND_MAX + 10;
	ang_speed = float(rand())/RAND_MAX/50;
	scale = pow(2.0, (rand()%3 + 1))*4.0f;
	radius *= scale;
	mass = 4.0f/3.0f * D3DX_PI * radius * radius * radius;
	velocity *= speed;
	
	D3DXMatrixScaling(&m_scale, scale, scale, scale);
    D3DXMatrixTranslation(&world, -vCenter.x, -vCenter.y, -vCenter.z );
	D3DXMatrixRotationYawPitchRoll(&rotation, ang_speed*angular.x, ang_speed*angular.y, ang_speed*angular.z);

	//For ship movement
	Current_Vec = D3DXVECTOR3(0,0,0);
	f_xTranslation = f_yTranslation = f_zTranslation = 0;
	b_xTranslation = b_yTranslation = b_zTranslation = false;
}

Asteroid::Asteroid(const Asteroid &copy)
{
	this->
	world = copy.world;
	rotation = copy.rotation;
	m_scale = copy.m_scale;
	position = copy.position;
	velocity = copy.velocity;
	angular = copy.angular;
	radius = copy.radius;
	ang_speed = copy.ang_speed;
	scale = copy.scale;
	mass = copy.mass;

	//For ship movement
	Current_Vec = D3DXVECTOR3(0,0,0);
	f_xTranslation = f_yTranslation = f_zTranslation = 0;
	b_xTranslation = b_yTranslation = b_zTranslation = false;
}

Asteroid::~Asteroid()
{
	//cleanup();
}

void Asteroid::cleanup()
{
	//release everything created
	SAFE_RELEASE( mesh );
	SAFE_RELEASE( meshTexture );
	SAFE_RELEASE( bumpTexture );
}
//Ship does not move, asteriods do
void Asteroid::keyboard()
{
	bool* upgrades = graphics.getUpgrades();
	float speed_cap = 0.50f;
	if(	upgrades[THRUSTER_TYPED] )
		speed_cap = 0.80f;
	//Reset values to 0
	f_xTranslation = f_yTranslation = f_zTranslation = 0;


		//Check to see if ship has energy
	if( !graphics.HUD_EnergyStateMin() )
	{	
		if( GetKeyState(0x57) & 0x80 ) //W
		{
			//if(f_zTranslation < speed_cap)
			//{
				if(	!upgrades[THRUSTER_TYPED] )
					f_zTranslation = 0.05f;
				else
					f_zTranslation =0.09f;
				b_zTranslation = true;

				graphics.EFFECTS_renderThruster();
				float t = graphics.EFFECTS_getThrusterDrainRate();
				//graphics.HUD_AdjustEnergyLevel( graphics.EFFECTS_getThrusterDrainRate() );
			//}
		}

		if( GetKeyState(0x53) & 0x80 ) //S
		{
			//if(f_zTranslation > -speed_cap)
			//{
				if(	!upgrades[THRUSTER_TYPED] )
					f_zTranslation = -0.05f;
				else
					f_zTranslation = -0.09f;
				b_zTranslation = true;
				graphics.EFFECTS_renderThruster();
				//graphics.HUD_AdjustEnergyLevel( graphics.EFFECTS_getThrusterDrainRate() );
			//}
		}

		//Only if you have auxillary thrusters
		if(	!upgrades[THRUSTER_MARKI] )
		{
			if( GetKeyState(0x41) & 0x80 ) //A
			{
				f_xTranslation = -0.025f;
				b_xTranslation = true;
				graphics.EFFECTS_renderAuxThrusterRight();
				//graphics.HUD_AdjustEnergyLevel( graphics.EFFECTS_getThrusterDrainRate()/2.0f );
			}

			if( GetKeyState(0x44) & 0x80 ) //D
			{
				f_xTranslation = 0.025f;
				b_xTranslation = true;
				graphics.EFFECTS_renderAuxThrusterLeft();
				//graphics.HUD_AdjustEnergyLevel( graphics.EFFECTS_getThrusterDrainRate()/2.0f );
			}	
		}
	
	
	}//End EnergyState()
}

void Asteroid::LoadModel()
{
	LPD3DXBUFFER	materialBuffer;

	// Load the mesh from the specified file
	D3DXLoadMeshFromX(_T("rocks/rock2.x"), D3DXMESH_MANAGED, 
							graphics.getDevice(), NULL, 
							&materialBuffer, NULL, &numMaterials, 
							&mesh );

	//set up material and texture
	d3dxMaterials = (D3DXMATERIAL*)materialBuffer->GetBufferPointer();

	meshTexture  = NULL;
	meshMaterials = new D3DMATERIAL9[numMaterials];

	for (DWORD i=0; i<numMaterials; i++)
	{
		// Copy the material
		meshMaterials[i] = d3dxMaterials[i].MatD3D;

		// Set the ambient color for the material (D3DX does not do this)
		meshMaterials[i].Ambient = meshMaterials[i].Diffuse;
     
		// Create the texture if it exists - it may not
		//meshTextures[i] = NULL;
		//if (d3dxMaterials[i].pTextureFilename)
		//	D3DXCreateTextureFromFile(graphics.getDevice(), d3dxMaterials[i].pTextureFilename, &meshTextures[i]);
	}

	D3DXCreateTextureFromFile(graphics.getDevice(), _T("rocks/rock2.jpg"), &meshTexture);
	D3DXCreateTextureFromFile(graphics.getDevice(), _T("rocks/normal2.jpg"), &bumpTexture);

	SAFE_RELEASE( materialBuffer );
}

void Asteroid::updatePos()
{
	position += velocity*graphics.getTimeDifference();

	for(int i=0; i<3; i++)
	{
		if(position[i] > bound)
			position[i] = -bound;
		else if(position[i] < -bound)
			position[i] = bound;
	}
}

void Asteroid::prerender()
{
	LPDIRECT3DDEVICE9 device = graphics.getDevice();
	
	//graphics.setLight();

	device->SetFVF( mesh->GetFVF() );

	//device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
	//device->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TEXTURE);
	//device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);	

	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	//device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID );

	//device->SetTexture(0,Asteroid::meshTexture);
	//device->SetTexture(0,NULL);
}

void Asteroid::render( const D3DXMATRIX &level_rot )
{
	keyboard();
	updatePos();

	LPDIRECT3DDEVICE9 device = graphics.getDevice();

	D3DXMATRIX temp_rot;
	D3DXMatrixRotationYawPitchRoll(&temp_rot, ang_speed*angular.x, ang_speed*angular.y, ang_speed*angular.z);
	rotation = rotation * temp_rot;

	//==============================================================================================
	//Use pre-computed rotations to rotate and translate the asteroids
	//From ship movement
	//==============================================================================================
	D3DXMATRIX ship_rot = graphics.getShipRotation();
	//Find inverse rotation
	D3DXMATRIX inverse_ship_rot;
	D3DXMatrixInverse(&inverse_ship_rot, NULL, &ship_rot);
	//Make ship vector based on z direction
	D3DXVECTOR3 ship_vector = D3DXVECTOR3(f_xTranslation,f_yTranslation,f_zTranslation);
	
	//D3DXMATRIX inverse_level_rot;
	//D3DXMatrixInverse(&inverse_level_rot, NULL, &level_rot);
	
	//Rotate the vector based on ship rotation
	D3DXVec3TransformNormal(&ship_vector,&ship_vector,&ship_rot);

	if( b_zTranslation || b_xTranslation)
	{	
		setShipVelocity( (ship_vector));
		b_zTranslation = false;
		b_xTranslation = false;
		Current_Vec += getShipVelocity();
	}
	
	 
	//Adjust current_vec of asteroids to continue their path
	D3DXVec3TransformNormal(&Current_Vec,&Current_Vec,&level_rot);
	D3DXVec3TransformCoord(&position,&position,&level_rot);
	//Translate asteroids based on ship z-movement
	position -= Current_Vec;
	//Translate the position to its rotated position
	


	
	D3DXMATRIX trans;
	D3DXMatrixTranslation(&trans, position.x, position.y , position.z);
	
	D3DXMatrixScaling(&m_scale, scale, scale , scale);
	//==============================================================================================
	//==============================================================================================

	D3DXMATRIX transform = world*m_scale*rotation*trans;//*level_rot;
	//device->SetTransform(D3DTS_WORLD, &(m_scale*trans));
	//
	////graphics.setLight();

	//device->SetFVF( mesh->GetFVF() );

	//device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
	//device->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TEXTURE);
	//device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);	

	//device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	//device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID );

	//device->SetTexture(0,meshTexture);

	//for (DWORD i=0; i<numMaterials; i++)
	//{
	//   // Set the material and texture for this subset
	//  device->SetMaterial(&meshMaterials[i]);
 //       
	//  // Draw the mesh subset
	//  mesh->DrawSubset( i );
	//}

//pixel shading
	//device->SetRenderState(D3DRS_LIGHTING, FALSE);

	//device->SetTransform(D3DTS_WORLD, &transform);

	graphics.ShadeBump(&transform, meshMaterials[1], mesh, meshTexture, bumpTexture, numMaterials);//
}

D3DXVECTOR3 Asteroid::getPosition()
{
	return position;
}
void Asteroid::setPosition(const D3DXVECTOR3 *pos)
{
	position = *pos;
}
D3DXVECTOR3 Asteroid::getVelocity()
{
	return velocity;
}
void Asteroid::setVelocity(const D3DXVECTOR3 *vel)
{
	velocity = *vel;
}
D3DXMATRIX Asteroid::getRotation()
{
	return rotation;
}
void Asteroid::setRotation(const D3DXMATRIX *rot)
{
	rotation = *rot;
}
float Asteroid::getScale()
{
	return scale;
}
void Asteroid::setScale(float scale)
{
	radius /= this->scale;
	this->scale = scale;
	radius *= scale;
	//change mass
}
float Asteroid::getAngSpeed()
{
	return ang_speed;
}
void Asteroid::setAngSpeed(float speed)
{
	this->ang_speed = speed;
}
float Asteroid::getRadius()
{
	return radius;
}
float Asteroid::getMass()
{
	return mass;
}
void Asteroid::setSpeed(float speed)
{
	D3DXVec3Normalize(&velocity, &velocity);
	velocity *= speed;
	//this->speed = speed;
}
void Asteroid::setShipVelocity(const D3DXVECTOR3 &newVelocity)
{
	graphics.setShipVelocity(newVelocity);
}
D3DXVECTOR3 Asteroid::getShipVelocity()
{
	return graphics.getShipVelocity();
}
//D3DXMATRIX Asteroid::CheckCrosshairBounds( D3DXVECTOR3 v_Crosshair )
//{
//	float yaw, pitch, roll;
//	yaw = pitch = roll = 0.0f;
//	//Check x bounds
//	//if(v_Crosshair.x<=150.0f){	yaw = 0.003f; }
//	//else if(v_Crosshair.x>=650.0f){	yaw = -0.003f; }
//	////Check y bounds
//	//if(v_Crosshair.y<=100.0f){	pitch = 0.003f; }
//	//else if(v_Crosshair.y>=500.0f){	pitch = -0.003f; }
//
//	pitch = ( ( (-v_Crosshair.y/600.0f)+0.5f ) * (5.0f*D3DX_PI/2.0f) )/500.0f;
//	yaw = ( ( (-v_Crosshair.x/800.0f)+0.5f ) * (5.0f*D3DX_PI/2.0f) )/500.0f;
//	D3DXMATRIX tr;
//	D3DXMatrixRotationYawPitchRoll(&tr,yaw,pitch,roll);
//	return tr;
//}