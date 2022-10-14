#include "Graphics.h"
#include "DirectInput.h"
#include "Ship.h"

extern Graphics graphics;
extern DirectInput mouse;

Ship::Ship()
{
	position = D3DXVECTOR3(0,0,0);
	velocity = D3DXVECTOR3(0,0,0);
	speed = 0.0f;
	scale = 4.0f;
	radius *= scale;

	D3DXMatrixScaling(&world, scale, scale, scale);
	D3DXMatrixIdentity(&rotation);

	D3DXMATRIX xr;
	D3DXMATRIX yr;
	D3DXMATRIX xoffset;
	D3DXMatrixRotationX(&xoffset,-0.12f);
	D3DXMatrixRotationX(&xr,D3DX_PI/2.0f);
	D3DXMatrixRotationY(&yr,D3DX_PI/2.0f);
	world = world*xr*yr*xoffset;
	//rotation = world;
	

	xTranslation = yTranslation = zTranslation = 0;
	zRotation = xRotation = yRotation = 0;

	v_Crosshair = D3DXVECTOR3(400.0f,300.0f,1.0f);
	Crosshair_Object = D3DXVECTOR3(0.0f,0.0f,80.0f);
}

Ship::~Ship()
{
	cleanup();
}
void Ship::keyboard( )
{
	if( GetKeyState(0x41) & 0x80 ) //A
		xTranslation -= 0.1;

	if( GetKeyState(0x44) & 0x80 ) //D
		xTranslation += 0.1;

	if( GetKeyState(0x57) & 0x80 ) //W
		zTranslation += 0.1;

	if( GetKeyState(0x53) & 0x80 ) //S
		zTranslation -= 0.1;

	if( GetKeyState(0x5A) & 0x80 ) //Z
		zTranslation -= 0.01;

	if( GetKeyState(0x58) & 0x80 ) //X
		zTranslation += 0.01;
}
void Ship::cleanup()
{
	//release texture
	SAFE_RELEASE( mesh );
	SAFE_RELEASE( meshTexture );
	SAFE_RELEASE( bumpTexture );
}

void Ship::LoadModel()
{
	LPD3DXBUFFER	materialBuffer;

	// Load the mesh from the specified file
	D3DXLoadMeshFromX(_T("ship/ship.x"), D3DXMESH_MANAGED, 
							graphics.getDevice(), NULL, 
							&materialBuffer, NULL, &numMaterials, 
							&mesh );

	//set up material and texture
	d3dxMaterials = (D3DXMATERIAL*)materialBuffer->GetBufferPointer();

	meshTexture = NULL;
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
		//	 D3DXCreateTextureFromFile(graphics.getDevice(), d3dxMaterials[i].pTextureFilename, &meshTextures[i]);
	}
	
	D3DXCreateTextureFromFile(graphics.getDevice(), _T("ship/ship.jpg"), &meshTexture);
	D3DXCreateTextureFromFile(graphics.getDevice(), _T("ship/bump.jpg"), &bumpTexture);

	SAFE_RELEASE( materialBuffer );

	//Setup sprite
	D3DXCreateSprite(graphics.getDevice(), &hanger);
	D3DXCreateTextureFromFile( 	graphics.getDevice(), _T("images/crosshair3.png"), &pTexture );

	
	//Compute a bounding sphere for the mesh
	D3DXVECTOR3* pData;
    D3DXVECTOR3 vCenter;
    mesh->LockVertexBuffer( 0, ( LPVOID* )&pData );
    D3DXComputeBoundingSphere( pData, mesh->GetNumVertices(), D3DXGetFVFVertexSize( mesh->GetFVF() ), &vCenter, &radius );
    mesh->UnlockVertexBuffer();

	D3DXMATRIX trans;
	D3DXMatrixTranslation(&trans, vCenter.x, vCenter.y, vCenter.z);
}

D3DXVECTOR3 Ship::getCrosshairPosition()
{
	return v_Crosshair;
}

void Ship::render()
{
	//Get keyboard data
	keyboard();
	//Get mouse data
	DIMOUSESTATE mstate = mouse.GetMouseState();


	LPDIRECT3DDEVICE9 device = graphics.getDevice();


	//PITCH OF SHIP i.e xRotation
	//Use spritepos.y

	//find rotation value
	float xRot = ( ( (-v_Crosshair.y/600.0f)+0.5f ) * (D3DX_PI/2.0f) )+0.12f;
	D3DXMATRIX xr;
	D3DXMatrixRotationX(&xr, -xRot );
	
	//YAW OF SHIP i.e yRotation
	//Use spritepos.x

	//find rotation value
	float yRot = ( ( (-v_Crosshair.x/800.0f)+0.5f ) * (D3DX_PI/2.0f) );
	D3DXMATRIX yr;
	D3DXMatrixRotationY(&yr, -yRot );


	//Set the current rotation of the ship
	setRotation( &(xr*yr) );

	//Transform world
	D3DXMATRIX transform = world*rotation;
	//device->SetTransform(D3DTS_WORLD, &(world*rotation*world) );

	
	//graphics.setLight();

	//device->SetFVF( mesh->GetFVF() );

	device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
	device->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TEXTURE);
	device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);

	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID );

	//device->SetTexture(0,meshTexture);

	//graphics.setMaterial();

	graphics.ShadeBump(&transform, meshMaterials[0], mesh, meshTexture, bumpTexture, numMaterials);//




	//RENDER SPRITE CROSSHAIR
	//Sprite Background
	
	if(mstate.lX>0 && v_Crosshair.x<=(775.0f))		//775
	{
		v_Crosshair.x+=10.0f;
		Crosshair_Object.x+=2.0f;
	}
	else if(mstate.lX<0 && v_Crosshair.x>=(20.0f))	//20
	{
		v_Crosshair.x-=10.0f;
		Crosshair_Object.x-=2.0f;
	}
	if(mstate.lY>0 && v_Crosshair.y<=(575.0f))		//575
	{
		v_Crosshair.y+=10.0f;
		Crosshair_Object.y-=2.0f;
	}
	else if(mstate.lY<0 && v_Crosshair.y>=(100.0f) )	//20
	{
		v_Crosshair.y-=10.0f;
		Crosshair_Object.y+=2.0f;
	}

	
	D3DXMATRIX sprite_trans;
	D3DXMATRIX sprite_scale;
	D3DXVECTOR3 v_trans = D3DXVECTOR3(0.0f,0.0f,80.0f);
	D3DXMatrixIdentity(&sprite_scale);

	D3DXMatrixScaling(&sprite_scale,0.25f,0.25f,1.0f);
	D3DXVec3TransformCoord(&v_trans,&v_trans,&(rotation));
	D3DXMatrixTranslation(&sprite_trans, v_trans.x, v_trans.y+10.0f, v_trans.z );
	
	
	hanger->SetWorldViewLH(NULL, &(graphics.GetView()) );
	
	hanger->Begin(D3DXSPRITE_ALPHABLEND|D3DXSPRITE_OBJECTSPACE|D3DXSPRITE_BILLBOARD);
	hanger->Draw(pTexture,NULL ,&D3DXVECTOR3(16.0f,16.0f,0.0f),NULL,0xFFFFFFFF);

	//hanger->
	hanger->SetTransform(&(sprite_scale*sprite_trans));
	hanger->End();
}


void Ship::setTranslation(D3DXMATRIX &tr)
{
	translation = tr;
}
D3DXMATRIX Ship::getTranslation()
{
	return translation;
}

D3DXVECTOR3 Ship::getPosition()
{
	return position;
}
//void Ship::setPosition(const D3DXVECTOR3 *pos)
//{
//	position = *pos;
//}
D3DXVECTOR3 Ship::getVelocity()
{
	return velocity;
}
void Ship::setVelocity(const D3DXVECTOR3 vel)
{
	/*bool* ups = graphics.getUpgrades();
	float speed_cap = 1.0f;
	if(	ups[THRUSTER_TYPED] )
		speed_cap = 3.2f;
	if(D3DXVec3Length(&vel) < speed_cap )
		velocity += vel;*/
	velocity = vel;

}
D3DXMATRIX Ship::getRotation()
{
	return rotation;
}
void Ship::setRotation(const D3DXMATRIX *rot)
{
	rotation = *rot;
}
void Ship::setScale(float scale)
{
	this->scale = scale;
}
void Ship::setSpeed(float speed)
{
	this->speed = speed;
}
float Ship::getRadius()
{
	return radius;
}