#include "Effects.h"
#include "Graphics.h"
#include "DirectInput.h"
#include "Hud.h"

extern DirectInput mouse;
extern Graphics graphics;

DWORD					Effects::numMaterials;
LPDIRECT3DTEXTURE9		Effects::meshTexture;
D3DMATERIAL9*			Effects::meshMaterials;
D3DXMATERIAL*			Effects::d3dxMaterials;
LPD3DXMESH				Effects::mesh;
D3DXMATRIX				Effects::start_pos;

//Laser Struct init function
Laser::Laser( D3DXMATRIX rot )
{
	position = D3DXVECTOR3(0.0f,0.0f,5.0f);		//Initial position infront of ship
	direction = D3DXVECTOR3(0.0f,0.0f,1.0f);
	//Transform initial direction to ship direction
	D3DXVec3TransformCoord(&position,&position, &rot);
	//get direction of bullet
	D3DXVec3TransformCoord(&direction,&direction, &rot);
	//direction = graphics.getCrosshairPosition() - position;
	//Adjust direction for crosshair
	direction.y +=0.12;
	//normalize direction
	D3DXVec3Normalize(&direction,&direction);

	//Check for GUN_GATLIN Upgrade
	bool* ups = graphics.getUpgrades();
	float s = 5.0f;
	if(ups[GUN_GATLIN])
		float s = 20.0f;

	//Set direction based on bullet speed and unit vector of ship
	direction *= s;
}


Effects::Effects()
{
	//light_position = D3DXVECTOR3(15.0f,15.0f,15.0f);
	light_position = D3DXVECTOR3(0.0f,15.0f,15.0f);
	//D3DXVec3Normalize(&light_direction,&(-1.0f*light_position));
	light_direction = D3DXVECTOR3(0.0f,-1.0f,-1.0f);
	/*light = new Lights[4];
	light_position = new D3DXVECTOR3[4];
	light_direction = new D3DXVECTOR3[4];
	light_position[0] = &D3DXVECTOR3(0.0f,0.0f,20.0f);
	light_position[1] = &D3DXVECTOR3(20.0f,0.0f,0.0f);
	light_position[2] = &D3DXVECTOR3(0.0f,0.0f,-20.0f);
	light_position[3] = &D3DXVECTOR3(-20.0f,0.0f,0.0f);
	light_direction[0] = &D3DXVECTOR3(0.0f,0.0f,-1.0f);
	light_direction[1] = &D3DXVECTOR3(-1.0f,0.0f,0.0f);
	light_direction[2] = &D3DXVECTOR3(0.0f,0.0f,1.0f);
	light_direction[3] = &D3DXVECTOR3(1.0f,0.0f,0.0f);*/
	//laser = new Laser[20];
	open = new bool[20];
	laser_count = 0;
	memset(open,false,sizeof(open));

	D3DXMATRIX xr;
	D3DXMATRIX yr;
	D3DXMATRIX xoffset;
	D3DXMatrixRotationX(&xoffset,-0.12f);
	D3DXMatrixRotationX(&xr,D3DX_PI/2.0f);
	D3DXMatrixRotationY(&yr,D3DX_PI/2.0f);
	start_pos = xr*yr*xoffset;
}
Effects::~Effects()
{
	cleanup();
}

void Effects::cleanup()
{
	//release any effects
	SAFE_RELEASE( Bullet );
	SAFE_RELEASE( Shield );
	SAFE_RELEASE( mesh );
}
void Effects::Initialize()
{
	//Energy
	energy_charge_rate = 0.4f;
	thruster_drain_rate = -0.8f;
	//Init Bullet sprite
	D3DXCreateSprite(graphics.getDevice(), &Bullet);
	D3DXCreateTextureFromFile( graphics.getDevice(), _T("images/S_redorb.png"), &Bullet_Texture);
	//Init Shield sprite
	D3DXCreateSprite(graphics.getDevice(), &Shield);
	D3DXCreateTextureFromFile( graphics.getDevice(), _T("images/s_shield.png"), &Shield_Texture);
	//Init Thruster sprite
	D3DXCreateSprite(graphics.getDevice(), &Thrust);
	D3DXCreateTextureFromFile( graphics.getDevice(), _T("ship/thruster2.tga"), &Thrust_Texture);
	//Init AuxThrusterL sprite
	D3DXCreateSprite(graphics.getDevice(), &AuxThrustLU);
	D3DXCreateSprite(graphics.getDevice(), &AuxThrustLD);
	D3DXCreateTextureFromFile( graphics.getDevice(), _T("ship/AuxThrusterL_U30.png"), &AuxThrustL_U30_Texture);
	D3DXCreateTextureFromFile( graphics.getDevice(), _T("ship/AuxThrusterL_D30.png"), &AuxThrustL_D30_Texture);
	//Init AuxThrusterR sprite
	D3DXCreateSprite(graphics.getDevice(), &AuxThrustRU);
	D3DXCreateSprite(graphics.getDevice(), &AuxThrustRD);
	D3DXCreateTextureFromFile( graphics.getDevice(), _T("ship/AuxThrusterR_U30.png"), &AuxThrustR_U30_Texture);
	D3DXCreateTextureFromFile( graphics.getDevice(), _T("ship/AuxThrusterR_D30.png"), &AuxThrustR_D30_Texture);
	//=================================================================
	//Ship Mesh for shield
	//=================================================================
	shield_energy = -1.8f;

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
	
	D3DXCreateTextureFromFile(graphics.getDevice(), _T("ship/shield_screen3.png"), &meshTexture);

	SAFE_RELEASE( materialBuffer );

}
void Effects::render()
{
	//Get mouse data
	DIMOUSESTATE mstate = mouse.GetMouseState();
	//Get Upgrades
	bool* upgrades = graphics.getUpgrades();
	//If the laser_list is not empty
	//check boundry
	if( !laser_list.empty() )
	{
		//laser_list iterator
		list<Laser>::iterator pos = laser_list.begin();
		//Check bullet distance - 250 away from origin, delete
		//Only need to check first bullet in list
		if( pos->magnitude >= 500.0f)
		{
			laser_list.pop_front();
			laser_count--;
		}

		list<Asteroid> asteroids = *graphics.LEVEL_getAsteroids();

		for(list<Laser>::iterator i=laser_list.begin(); i!=laser_list.end(); i++)
		{
			for(list<Asteroid>::iterator j=asteroids.begin(); j!=asteroids.end(); j++)
			{
				D3DXVECTOR3 norm = i->position - j->getPosition();

				float r = j->getRadius();

				if(abs(norm.x) <= r && abs(norm.y) <= r && abs(norm.z) <= r)
				{
					j = graphics.LEVEL_Split(j);
					i = laser_list.erase(i);
					//graphics.PlaySoundA("
				}
			}
		}
	}


	//Check to see if ship has energy
	if( !graphics.HUD_EnergyStateMin() )
	{
		if(mstate.rgbButtons[0] & 0x80)
		{
			if(laser_count<20)
			{
				Laser laser( graphics.getShipRotation() );//CheckCrosshairBounds(graphics.getCrosshairPosition()));
				//Play fire sound
				//laser.sound.PlaySound("fire.wav");
				//Increment laser_count
				laser_count++;
				//Push into list
				laser_list.push_back(laser);
				(--laser_list.end())->sound.PlaySoundA("fire.wav");
				//Energy consumption
				graphics.HUD_AdjustEnergyLevel( -1.05f );
			}
		}
	}//End EnergyState()

		for(list<Laser>::iterator pos = laser_list.begin(); pos!=laser_list.end(); pos++)
		{
			//Adjust position and direction based on level_rot
			D3DXVec3TransformCoord(&pos->position,&pos->position,&graphics.LEVEL_getLevelRotation() );
			D3DXVec3TransformNormal(&pos->direction,&pos->direction,&graphics.LEVEL_getLevelRotation());
			//D3DXVec3Normalize(&pos->direction,&pos->direction);

			pos->position += pos->direction;
			pos->magnitude = D3DXVec3Length(&(pos->position));
			renderBullet( pos->position );
		}
	//Check to see if ship has energy
	if( !graphics.HUD_EnergyStateMin() )
	{	
		if( GetKeyState(0x57) & 0x80 ) //W
		{
			//renderThruster();
			graphics.HUD_AdjustEnergyLevel( thruster_drain_rate );
		}
		if( GetKeyState(0x53) & 0x80 ) //S
		{
			graphics.HUD_AdjustEnergyLevel( thruster_drain_rate );
		}
		if( GetKeyState(0x41) & 0x80 ) //A
		{
			graphics.HUD_AdjustEnergyLevel( thruster_drain_rate/1.5f );
		}
		if( GetKeyState(0x44) & 0x80 ) //D
		{
			graphics.HUD_AdjustEnergyLevel( thruster_drain_rate/1.5f );
		}
		//Check to see if you have a shield to use otherwise do not render a shield
		if( !upgrades[SHIELD_AMP] || upgrades[SHIELD_PROTO] )
			if( (graphics.HUD_EnergyShieldStateMin()==false && graphics.HUD_ShieldState()==false) || (graphics.HUD_EnergyShieldStateMin()==true && graphics.HUD_ShieldState()==true) || (graphics.HUD_EnergyShieldStateMin()==false && graphics.HUD_ShieldState()==true))
				if( mstate.rgbButtons[1] & 0x80)
				{
					graphics.getDevice()->SetRenderState(D3DRS_LIGHTING,true);
					renderShield();
					//Adjust Energy Level
					graphics.HUD_AdjustEnergyLevel( shield_energy );
					graphics.HUD_SetShieldUse(true);
					graphics.getDevice()->SetRenderState(D3DRS_LIGHTING,false);
				}
	}//End EnergyState()
	//If mouse is released
	if( graphics.HUD_EnergyStateMin() && graphics.HUD_ShieldState() )
		graphics.HUD_SetShieldUse(false);
	//Energy Slowly regenerates
	if( !graphics.HUD_EnergyStateMax() )
		graphics.HUD_AdjustEnergyLevel( energy_charge_rate );
}
void Effects::renderBullet( D3DXVECTOR3 position )
{
	D3DXMATRIX sprite_trans;
	D3DXMATRIX sprite_scale;
	//D3DXVECTOR3 v_trans = D3DXVECTOR3(position.x,position.y,position.z);
	D3DXMatrixIdentity(&sprite_scale);

	D3DXMatrixScaling(&sprite_scale,0.125f,0.125f,1.0f);

	//D3DXVec3TransformCoord(&v_trans,&v_trans,&direction) );
	D3DXMATRIX origin;
	//D3DXMatrixTranslation(&origin,-position.x,-position.y,-position.z);
	//D3DXMATRIX level_rot = -1.0f*graphics.LEVEL_getLevelRotation();
	//D3DXVec3TransformCoord(&position,&position,&graphics.LEVEL_getLevelRotation() );
	D3DXMatrixTranslation(&sprite_trans, position.x, position.y, position.z );
	
	
	Bullet->SetWorldViewLH(NULL, &(graphics.GetView()) );
	
	Bullet->Begin(D3DXSPRITE_ALPHABLEND|D3DXSPRITE_OBJECTSPACE|D3DXSPRITE_BILLBOARD| D3DXSPRITE_SORT_DEPTH_BACKTOFRONT);
	Bullet->Draw(Bullet_Texture,NULL ,&D3DXVECTOR3(8.0f,8.0f,0.0f),NULL,0x55FFFFFF);

	//hanger->
	Bullet->SetTransform(&(sprite_scale*sprite_trans));
	Bullet->End();

}
void Effects::renderShield()
{
	LPDIRECT3DDEVICE9 device = graphics.getDevice();
	//Setup light for the shield
	//for(int i =0; i<4; i++)
		light.SetShieldLight( light_position, light_direction );
		graphics.setLight(light, 0);

	//Rotate light for next render
	rotateShieldLight();

	D3DXMATRIX trans[6];
	//D3DXMatrixTranslation(&trans[0],0.0f,0.0f,0.0f);
	D3DXMatrixTranslation(&trans[0],0.3f,0.0f,0.0f);
	D3DXMatrixTranslation(&trans[1],-0.3f,0.0f,0.0f);
	D3DXMatrixTranslation(&trans[2],0.0f,0.3f,0.0f);
	D3DXMatrixTranslation(&trans[3],0.0f,-0.3f,0.0f);
	D3DXMatrixTranslation(&trans[4],0.0f,0.0f,0.3f);
	D3DXMatrixTranslation(&trans[5],0.0f,0.0f,-0.3f);

	for(int i=0; i<6; i++)
	{
		//MESH
		D3DXMATRIX shield_scale;
		D3DXMatrixScaling(&shield_scale,4.0f,4.0f,4.0f);
		//Transform world
		device->SetTransform(D3DTS_WORLD, &(shield_scale*start_pos*graphics.getShipRotation()*trans[i]) );

	
		//graphics.setLight();

		device->SetFVF( mesh->GetFVF() );

		device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
		device->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TEXTURE);
		device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);	

		device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		device->SetRenderState(D3DRS_BLENDOP,D3DBLENDOP_ADD);

		device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE );
		device->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

		/*device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
		device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID );*/

		device->SetTexture(0,meshTexture);

		for (DWORD i=0; i<numMaterials; i++)
		{
		   // Set the material and texture for this subset
		  device->SetMaterial(&meshMaterials[i]);
        
		  // Draw the mesh subset
		  mesh->DrawSubset( i );
		}
		device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW );
		device->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
		device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	}

}
D3DXMATRIX Effects::CheckCrosshairBounds( D3DXVECTOR3 v_Crosshair )
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
void Effects::rotateShieldLight()
{
	D3DXMATRIX xr;
	D3DXMATRIX yr;
	D3DXMATRIX zr;
	D3DXMatrixRotationX(&xr,D3DX_PI/60.0f);
	//D3DXMatrixRotationY(&yr,D3DX_PI/60.0f);
	D3DXMatrixRotationZ(&zr,D3DX_PI/60.0f);

	D3DXMATRIX r = xr*zr;//*yr*zr;//*yr;

	D3DXVec3TransformCoord(&light_position,&light_position,&r);
	D3DXVec3TransformCoord(&light_direction,&light_direction,&r);


	//light_position.y = pow( pow(light_position.x,2.0f), 0.5f);
}
void Effects::renderThruster()
{
	D3DXMATRIX sprite_trans;
	D3DXMATRIX sprite_scale;
	D3DXMATRIX rot = graphics.getShipRotation();
	D3DXVECTOR3 position = D3DXVECTOR3(0.0f,-1.0f,-5.5f);

	//Render SKYLIGHT
	light.SetThrusterLight();
	graphics.setLight(light,0);
	//D3DXVECTOR3 v_trans = D3DXVECTOR3(position.x,position.y,position.z);
	D3DXMatrixIdentity(&sprite_scale);

	D3DXMatrixScaling(&sprite_scale,0.025f,0.025f,0.025f);

	D3DXVec3TransformCoord(&position,&position,&rot);
	

	D3DXMatrixTranslation(&sprite_trans, position.x, position.y, position.z );
	
	
	Thrust->SetWorldViewLH(NULL, &(graphics.GetView()) );
	
	Thrust->Begin(D3DXSPRITE_ALPHABLEND|D3DXSPRITE_OBJECTSPACE|D3DXSPRITE_BILLBOARD| D3DXSPRITE_SORT_DEPTH_BACKTOFRONT );
	Thrust->Draw(Thrust_Texture,NULL ,&D3DXVECTOR3(64.0f,64.0f,0.0f),NULL,0x9FFFFFFF);

	//hanger->
	Thrust->SetTransform(&(sprite_scale*sprite_trans));
	Thrust->End();
}
//Render Auxillary thruster
void Effects::renderAuxThrusterRight()
{
	D3DXMATRIX sprite_trans;
	D3DXMATRIX sprite_scale;
	D3DXMATRIX rot = graphics.getShipRotation();

	D3DXMATRIX rotate_45D;
	D3DXMatrixRotationZ(&rotate_45D,D3DX_PI/4);

	D3DXMatrixIdentity(&sprite_scale);

	D3DXMatrixScaling(&sprite_scale,0.04f,0.04f,1.0f);

	D3DXVECTOR3 position = D3DXVECTOR3(1.0f,0.5f,-0.5f);
	D3DXVec3TransformCoord(&position,&position,&rot);
	

	D3DXMatrixTranslation(&sprite_trans, position.x, position.y, position.z );
	
	
	AuxThrustRU->SetWorldViewLH(NULL, &(graphics.GetView()) );

	AuxThrustRU->Begin(D3DXSPRITE_ALPHABLEND|D3DXSPRITE_OBJECTSPACE|D3DXSPRITE_BILLBOARD| D3DXSPRITE_SORT_DEPTH_BACKTOFRONT );
	AuxThrustRU->Draw(AuxThrustR_D30_Texture,NULL ,&D3DXVECTOR3(0.0f,0.0f,0.0f),NULL,0x35FFFFFF);
	AuxThrustRU->SetTransform(&(sprite_scale*sprite_trans));
	AuxThrustRU->End();

	AuxThrustRD->SetWorldViewLH(NULL, &(graphics.GetView()) );
	position = D3DXVECTOR3(1.0f,-0.7f,-0.5f);
	D3DXVec3TransformCoord(&position,&position,&rot);
	//position.y*=-1.0f;
	D3DXMatrixTranslation(&sprite_trans, position.x, position.y, position.z );
	AuxThrustRD->Begin(D3DXSPRITE_ALPHABLEND|D3DXSPRITE_OBJECTSPACE|D3DXSPRITE_BILLBOARD| D3DXSPRITE_SORT_DEPTH_BACKTOFRONT );
	AuxThrustRD->Draw(AuxThrustR_U30_Texture,NULL ,&D3DXVECTOR3(0.0f,64.0f,0.0f),&D3DXVECTOR3(0.0f,0.0f,0.0f),0x35FFFFFF);
	AuxThrustRD->SetTransform(&(sprite_scale*sprite_trans));
	AuxThrustRD->End();
}
void Effects::renderAuxThrusterLeft()
{
	D3DXMATRIX sprite_trans;
	D3DXMATRIX sprite_scale;
	D3DXMATRIX rot = graphics.getShipRotation();

	D3DXMATRIX rotate_45D;
	D3DXMatrixRotationZ(&rotate_45D,D3DX_PI/4);

	D3DXMatrixIdentity(&sprite_scale);

	D3DXMatrixScaling(&sprite_scale,0.04f,0.04f,1.0f);

	D3DXVECTOR3 position = D3DXVECTOR3(-1.0f,0.5f,-0.5f);
	D3DXVec3TransformCoord(&position,&position,&rot);
	

	D3DXMatrixTranslation(&sprite_trans, position.x, position.y, position.z );
	
	
	AuxThrustLU->SetWorldViewLH(NULL, &(graphics.GetView()) );

	AuxThrustLU->Begin(D3DXSPRITE_ALPHABLEND|D3DXSPRITE_OBJECTSPACE|D3DXSPRITE_BILLBOARD| D3DXSPRITE_SORT_DEPTH_BACKTOFRONT );
	AuxThrustLU->Draw(AuxThrustL_D30_Texture,NULL ,&D3DXVECTOR3(128.0f,0.0f,0.0f),NULL,0x55FFFFFF);
	AuxThrustLU->SetTransform(&(sprite_scale*sprite_trans));
	AuxThrustLU->End();

	AuxThrustLD->SetWorldViewLH(NULL, &(graphics.GetView()) );
	position = D3DXVECTOR3(-1.0f,-0.7f,-0.5f);
	D3DXVec3TransformCoord(&position,&position,&rot);
	//position.y*=-1.0f;
	D3DXMatrixTranslation(&sprite_trans, position.x, position.y, position.z );
	AuxThrustLD->Begin(D3DXSPRITE_ALPHABLEND|D3DXSPRITE_OBJECTSPACE|D3DXSPRITE_BILLBOARD| D3DXSPRITE_SORT_DEPTH_BACKTOFRONT );
	AuxThrustLD->Draw(AuxThrustL_U30_Texture,NULL ,&D3DXVECTOR3(128.0f,64.0f,0.0f),&D3DXVECTOR3(0.0f,0.0f,0.0f),0x55FFFFFF);
	AuxThrustLD->SetTransform(&(sprite_scale*sprite_trans));
	AuxThrustLD->End();
}
D3DXVECTOR3 Effects::GetSpotLightPosition()
{
	return spotlight.position;
}
D3DXVECTOR3 Effects::GetSpotLightDirection()
{
	return	spotlight.direction;
}

//===========================================================================
//Setting new values based on upgrades
//===========================================================================
void Effects::setShieldEnergyUse( float energy )
{
	shield_energy = energy;
}
void Effects::UpgradeToShieldProto()
{
	//Init Shield_texture to proto shield
	D3DXCreateTextureFromFile( graphics.getDevice(), _T("images/shieldproto.png"), &Shield_Texture);
	setShieldEnergyUse( -1.4f );
}
void Effects::UpgradeToGenTypeD()
{
	energy_charge_rate = 0.49f;
}
void Effects::UpgradeToGenTypeE()
{
	energy_charge_rate = 0.68;
}
void Effects::UpgradeToGunGatlin()
{
	//D3DXCreateTextureFromFile( graphics.getDevice(), _T("images/S_redorb.png"), &Bullet_Texture);
}
void Effects::UpgradeToGunProto()
{
	//D3DXCreateTextureFromFile( graphics.getDevice(), _T("images/S_redorb.png"), &Bullet_Texture);
}
void Effects::UpgradeToGunPoint()
{
}
void Effects::UpgradeToThrusterTypeD()
{
	thruster_drain_rate = -0.4;
}
void Effects::UpgradeToThrusterMarkI()
{
	//lets you have auxillary thrusters for strafing
}
float Effects::getThrusterDrainRate()
{
	thruster_drain_rate;
	return thruster_drain_rate;
}