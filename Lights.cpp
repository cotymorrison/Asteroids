#include "Lights.h"



Lights::Lights()
{
    ZeroMemory(&light, sizeof(D3DLIGHT9));
	
    light.Type = D3DLIGHT_POINT;

    light.Diffuse.r = 1.0f;
    light.Diffuse.g = 1.0f;
    light.Diffuse.b = 1.0f;

    light.Ambient.r = 1.0f;
    light.Ambient.g = 1.0f;
    light.Ambient.b = 1.0f;

    light.Specular.r = 0.0f;
    light.Specular.g = 0.0f;
    light.Specular.b = 0.0f;

    light.Position.x = 0.0f;
    light.Position.y = 0.0f;
    light.Position.z = 0.0f;

    light.Attenuation0 = 1.0f; 
    light.Attenuation1 = 0.0f; 
    light.Attenuation2 = 0.0f; 
    light.Range = 200.0f;
}
void Lights::SetSkyLight()
{
    ZeroMemory(&light, sizeof(D3DLIGHT9));
	
    light.Type = D3DLIGHT_POINT;

    light.Diffuse.r = 0.0f;
    light.Diffuse.g = 0.0f;
    light.Diffuse.b = 0.0f;

    light.Ambient.r = 0.5f;
    light.Ambient.g = 0.5f;
    light.Ambient.b = 0.5f;

    light.Specular.r = 0.0f;
    light.Specular.g = 0.0f;
    light.Specular.b = 0.0f;

    light.Position.x = 0.0f;
    light.Position.y = 0.0f;
    light.Position.z = 0.0f;

    light.Attenuation0 = 1.0f;
    light.Attenuation1 = 0.0f; 
    light.Attenuation2 = 0.0f; 
    light.Range = 2510.0f;
}

void Lights::SetShieldLight( D3DXVECTOR3 light_position, D3DXVECTOR3 light_direction )
{
	     // Fill in a light structure defining our light
      //D3DLIGHT9 light;
      ZeroMemory( &light, sizeof(D3DLIGHT9) );
      light.Type       = D3DLIGHT_DIRECTIONAL;
      light.Diffuse.r  = 80.0f;
      light.Diffuse.g  = 80.0f;
      light.Diffuse.b  = 80.0f;
      //light.Diffuse.a  = 1.0f;
	  light.Ambient.r	= .1f;
	  light.Ambient.g	= .1f;
	  light.Ambient.b	= .1f;
	  light.Ambient.a	= .2f;
	  light.Specular.r	= 1.0f;
	  light.Specular.g	= 1.0f;
	  light.Specular.b	= 1.0f;
	  light.Position	= light_position;
      light.Range      = 20.0f;

      // Create a direction for our light - it must be normalized 
  /*    D3DXVECTOR3 vecDir;
      vecDir = D3DXVECTOR3(0.0f,0.0f,0.0f);*/
      D3DXVec3Normalize( (D3DXVECTOR3*)&light.Direction, &light_direction );
}
void Lights::SetThrusterLight()
{
	ZeroMemory(&light, sizeof(D3DLIGHT9));
	
    light.Type = D3DLIGHT_POINT;

    light.Diffuse.r = 1.0f;
    light.Diffuse.g = 1.0f;
    light.Diffuse.b = 1.0f;

    light.Ambient.r = 1.0f;
    light.Ambient.g = 1.0f;
    light.Ambient.b = 1.0f;

    light.Specular.r = 1.0f;
    light.Specular.g = 1.0f;
    light.Specular.b = 1.0f;

    light.Position.x = 0.0f;
    light.Position.y = 0.0f;
    light.Position.z = 0.0f;
	
    light.Attenuation0 = 1.0f; 
    light.Attenuation1 = 0.0f; 
    light.Attenuation2 = 0.0f; 
    light.Range = 50.0f;
}
void Lights::SetPerimeterLight()
{
	ZeroMemory(&light, sizeof(D3DLIGHT9));
	
    light.Type = D3DLIGHT_POINT;

    light.Diffuse.r = 0.4f;
    light.Diffuse.g = 0.4f;
    light.Diffuse.b = 0.4f;

    light.Ambient.r = 0.4f;
    light.Ambient.g = 0.4f;
    light.Ambient.b = 0.4f;

    light.Specular.r = 0.4f;
    light.Specular.g = 0.4f;
    light.Specular.b = 0.4f;

    light.Position.x = 0.0f;
    light.Position.y = 0.0f;
    light.Position.z = 0.0f;
	
    light.Attenuation0 = 1.0f; 
    light.Attenuation1 = 0.0f; 
    light.Attenuation2 = 0.0f; 
    light.Range = 600.0f;
}
void Lights::SetShipViewLight( D3DXMATRIX ship_rot )
{
	D3DXVECTOR3 position = D3DXVECTOR3(0.0f,0.0f,5.0f);		//Initial position infront of ship
	D3DXVECTOR3 direction = D3DXVECTOR3(0.0f,0.0f,1.0f);
	//Transform initial direction to ship direction
	D3DXVec3TransformCoord(&position,&position, &ship_rot);
	//get direction of bullet
	D3DXVec3TransformCoord(&direction,&direction, &ship_rot);
	//direction = graphics.getCrosshairPosition() - position;
	//Adjust direction for crosshair
	direction.y +=0.12;
	//normalize direction
	D3DXVec3Normalize(&direction,&direction);

	// Fill in a light structure defining our light
	ZeroMemory( &spotlight, sizeof(D3DLIGHT9) );
	light.Type       = D3DLIGHT_SPOT;
	light.Diffuse.r  = 0.0f;
	light.Diffuse.g  = 0.0f;
	light.Diffuse.b  = 255.0f;
	//light.Diffuse.a  = 1.0f;
   
	light.Position = position;
	light.Direction = direction;
  
	// Tell the device about the light and turn it on
	light.Range=400.0f;
	light.Theta=0.05f;
	light.Phi=0.55f;
	light.Falloff=0.5f;
	light.Attenuation0= 1.0f;
}
D3DLIGHT9 Lights::getLight()
{
	return light;
}