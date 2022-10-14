#include "Hud.h"
#include "Graphics.h"
#include "DirectInput.h"
extern Graphics graphics;
extern DirectInput mouse;

Hud::Hud()
{

}
void Hud::Initialize()
{
	EnergyBarInit();
	energy_cap=100;

	LPDIRECT3DDEVICE9 device = graphics.getDevice();
	//Setup text
	AddFontResourceEx( "fonts/Coalition.ttf",FR_PRIVATE,0 );
	AddFontResourceEx( "fonts/Jacinto Sans.ttf",FR_PRIVATE,0 );
	AddFontResourceEx( "fonts/NIGHTSTALKER.ttf",FR_PRIVATE,0);
	AddFontResourceEx( "fonts/DS-DIGIB.ttf",FR_PRIVATE,0);
	

	D3DXCreateFont( device,
					24,
					0,
					FW_NORMAL,
					1,
					FALSE,
					DEFAULT_CHARSET,
					OUT_DEFAULT_PRECIS,
					ANTIALIASED_QUALITY,
					DEFAULT_PITCH|FF_DONTCARE,
					_T("Jacinto Sans"),
					&p_font_Words);
	D3DXCreateFont( device,
					36,
					0,
					FW_NORMAL,
					1,
					FALSE,
					DEFAULT_CHARSET,
					OUT_DEFAULT_PRECIS,
					ANTIALIASED_QUALITY,
					DEFAULT_PITCH|FF_DONTCARE,
					_T("DS-DIGITAL"),
					&p_font_Numbers);
}
void Hud::EnergyBarInit()
{
	//Initialize Power Meter
	D3DXMatrixScaling(&energy_bar.Meter_scale,1.0f,2.0f,1.0f);
	//Init Bullet sprite
	D3DXCreateSprite(graphics.getDevice(), &energy_bar.Meter);
	D3DXCreateTextureFromFile( graphics.getDevice(), _T("images/powermeter.png"), &energy_bar.Meter_Texture);

	cur_energy = 100;
	energy_bar.s=31.5f;
	D3DXMatrixScaling(&energy_bar.Energy_scale,4.0f,energy_bar.s,1.0f);
	//Init Bullet sprite
	D3DXCreateSprite(graphics.getDevice(), &energy_bar.Energy);
	D3DXCreateTextureFromFile( graphics.getDevice(), _T("images/s_energy.png"), &energy_bar.Energy_Texture);
	//Init Clone sprite
	D3DXMatrixScaling(&Clone_scale,0.5f,0.5f,1.0f);
//	for(int i=0;i<3;i++)
		D3DXCreateSprite(graphics.getDevice(), &Clone);
	D3DXCreateTextureFromFile( graphics.getDevice(), _T("images/clone.png"), &Clone_Texture);
}
void Hud::render()
{
	RECT rect;

	//========================================================
	//Render Energy Bar 
	//========================================================
	//Adjust Energy Bar based on current energy level	
	energy_bar.Energy->Begin(D3DXSPRITE_ALPHABLEND);
	energy_bar.Energy->Draw(energy_bar.Energy_Texture,NULL ,&D3DXVECTOR3(0.0f,16.0f,0.0f),&D3DXVECTOR3(0.0f,0.0f,0.0f),0x55FFFFFF);

	D3DXMATRIX t;
	////D3DXMatrixTranslation(&t,150.f,40.0f,0.0f);
	D3DXMatrixTranslation(&t,15.f,548.0f,0.0f);
	energy_bar.Energy_scale;
	energy_bar.Energy->SetTransform(&(energy_bar.Energy_scale*t));
	energy_bar.Energy->End();
	//========================================================
	//Render Power Meter over the energy bar
	//========================================================
	energy_bar.Meter->Begin(D3DXSPRITE_ALPHABLEND);
	energy_bar.Meter->Draw(energy_bar.Meter_Texture,NULL,&D3DXVECTOR3(0.0f,0.0f,0.0f),&D3DXVECTOR3(10.0f,20.0f,0.0f),0xAFFFFFFF);
	energy_bar.Meter->SetTransform(&(energy_bar.Meter_scale));
	energy_bar.Meter->End();
	
	//Show Energy
	rect.top = 565;
	rect.left = 5;
	rect.bottom = 600;
	rect.right = 140;
	
    p_font_Words->DrawText(NULL, "ENERGY ",-1,&rect,DT_LEFT,0xBB44AFDF);
	//Show Lives
	rect.top = 10;
	rect.left = 10;
	rect.bottom = 64;
	rect.right = 140;
	p_font_Words->DrawText(NULL, "LIVES: ",-1,&rect,DT_LEFT,0xBB44AFDF);
	
	//Show Clones sprite
	int lives = graphics.USER_getCurrentLives();
	for(float i=0;i<lives;i++)
	{
		Clone->Begin(D3DXSPRITE_ALPHABLEND);
		Clone->Draw(Clone_Texture,NULL,&D3DXVECTOR3(0.0f,0.0f,0.0f),&D3DXVECTOR3( (205.0f+45.0f*i), 20.0f, 0.0f),0xAFFFFFFF);
		Clone->SetTransform(&Clone_scale);
		Clone->End();
	}
	
	//Show Score
	int score = graphics.USER_getCurrentScore();
	rect.top = 10;
	rect.left = 540;
	rect.bottom = 64;
	rect.right = 640;
	p_font_Words->DrawText(NULL, "SCORE: ",-1,&rect,DT_LEFT,0xBB44AFDF);

	rect.top = 5;
	rect.left= 650;
	rect.right = 800;
	rect.bottom = 64;
	stringstream ss_score;
	ss_score << score;

	p_font_Numbers->DrawText(NULL, ss_score.str().c_str(),-1,&rect,DT_LEFT,0xBBFF0000);

}
bool Hud::EnergyStateMin()
{
	if(cur_energy<=1.0f)
		return true;
	return false;
}
bool Hud::EnergyStateMax()
{
	if(cur_energy==energy_cap)
		return true;
	return false;
}
bool Hud::EnergyShieldStateMin()
{
	if(cur_energy<25)
		return true;
	return false;
}
void Hud::SetShieldUse( bool use )
{
	shielduse = use;
}
bool Hud::ShieldState()
{
	return shielduse;
}
void Hud::AdjustEnergyLevel( float consumption )
{
	cur_energy+=consumption;
	if(cur_energy<0)
		cur_energy=0;
	if(cur_energy>energy_cap)
		cur_energy=energy_cap;
	float t = (energy_bar.s*cur_energy/energy_cap);
	D3DXMatrixScaling(&energy_bar.Energy_scale,4.0f,t,1.0f);
	energy_bar.Energy_scale;
}
void Hud::UpgradeToGenTypeD()
{
	energy_cap = 130;
}
void Hud::UpgradeToGenTypeE()
{
	energy_cap = 150;
}