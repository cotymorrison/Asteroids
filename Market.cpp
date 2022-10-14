#include "Graphics.h"
#include "Market.h"
using namespace std;
extern Graphics graphics;

Market::Market()
{
	upgrades = new bool[12];
	for(int i=0; i<12; i++)
		upgrades[i] = false;
	dollars = new int[12];

	dollars[SHIELD_AMP]		=	600;
	dollars[SHIELD_PROTO]	=	1500;
	dollars[GEN_TYPED]		=	500;
	dollars[GEN_TYPEE]		=	1200;
	dollars[GUN_GATLIN]		=	800;
	dollars[GUN_PROTO]		=	2000;
	dollars[GUN_POINT]		=	500;
	dollars[THRUSTER_TYPED] =	500;
	dollars[THRUSTER_MARKI] =	1500;

	money=100000;
}
Market::~Market()
{
	cleanup();
}
void Market::cleanup()
{
	SAFE_RELEASE(p_font_title);
	SAFE_RELEASE(p_font_subtitle);
	SAFE_RELEASE(p_font_price);
	SAFE_RELEASE(p_font_text);

	delete upgrades;
	delete dollars;
}
void Market::Initialize()
{
	LPDIRECT3DDEVICE9 device = graphics.getDevice();
	//Setup text
	AddFontResourceEx( "fonts/Coalition.ttf",FR_PRIVATE,0 );
	AddFontResourceEx( "fonts/Jacinto Sans.ttf",FR_PRIVATE,0 );
	AddFontResourceEx( "fonts/NIGHTSTALKER.ttf",FR_PRIVATE,0);
	AddFontResourceEx( "fonts/321impact.ttf",FR_PRIVATE,0);
	

	D3DXCreateFont( device,
					42,
					0,
					FW_NORMAL,
					1,
					FALSE,
					DEFAULT_CHARSET,
					OUT_DEFAULT_PRECIS,
					ANTIALIASED_QUALITY,
					DEFAULT_PITCH|FF_DONTCARE,
					_T("Jacinto Sans"),
					&p_font_title);
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
					_T("321impact"),
					&p_font_subtitle);

	D3DXCreateFont( device,
					20,
					0,
					FW_NORMAL,
					1,
					FALSE,
					DEFAULT_CHARSET,
					OUT_DEFAULT_PRECIS,
					ANTIALIASED_QUALITY,
					DEFAULT_PITCH|FF_DONTCARE,
					_T("Gill Sans Ultra Bold"),
					&p_font_price);
	D3DXCreateFont( device,
					20,
					0,
					FW_NORMAL,
					1,
					FALSE,
					DEFAULT_CHARSET,
					OUT_DEFAULT_PRECIS,
					ANTIALIASED_QUALITY,
					DEFAULT_PITCH|FF_DONTCARE,
					_T("321impact"),
					&p_font_text);
	D3DXCreateFont( device,
					31,
					0,
					FW_NORMAL,
					1,
					FALSE,
					DEFAULT_CHARSET,
					OUT_DEFAULT_PRECIS,
					ANTIALIASED_QUALITY,
					DEFAULT_PITCH|FF_DONTCARE,
					_T("DS-Digital"),
					&p_font_player);

	//Setup sprite
	D3DXCreateSprite(graphics.getDevice(), &hanger);
	D3DXCreateTextureFromFile( 	graphics.getDevice(), _T("images/hanger3.jpg"), &pTexture );
}
bool* Market::getUpgrades()
{
	return upgrades;
}
//Return money total
int Market::GetMoney()
{
	return money;
}
//Return dollars of upgrades list
int* Market::GetDollars()
{
	return dollars;
}
//Set money
void Market::SetMoney(int dollar)
{
	money += dollar;
}
//Keyboard controls for the market
void Market::keyboard()
{
	//Set Variables
	//bool* UPS = GetUpgrades();
	//int dollar = GetMoney();
	//int* cost = GetDollars();

	if(GetKeyState(0x31) & 0x80)	//1
		if(upgrades[SHIELD_AMP] == false)
			if(money >= dollars[SHIELD_AMP])
			{
				upgrades[SHIELD_AMP] = true;
				SetMoney( -dollars[SHIELD_AMP] );

				if(true) { int one = 1; }
			}
	if(GetKeyState(0x32) & 0x80)	//2
		if( upgrades[SHIELD_AMP] == true && upgrades[SHIELD_PROTO] == false)
			if(money >= dollars[SHIELD_PROTO])
			{
				upgrades[SHIELD_PROTO] = true;
				SetMoney( -dollars[SHIELD_PROTO]);
				graphics.EFFECTS_UpgradeToShieldProto();
			}
	if(GetKeyState(0x33) & 0x80)	//3
		if(upgrades[GEN_TYPED] == false)	
			if(money >= dollars[GEN_TYPED])
			{
				upgrades[GEN_TYPED] = true;
				SetMoney( -dollars[GEN_TYPED]);
			}
	if(GetKeyState(0x34) & 0x80)	//4
		if(upgrades[GEN_TYPED] == true && upgrades[GEN_TYPEE] == false)
			if(money >= dollars[GEN_TYPEE])
			{
				upgrades[GEN_TYPEE] = true;
				SetMoney( -dollars[GEN_TYPEE]);
			}
	if(GetKeyState(0x35) & 0x80)	//5
		if(upgrades[GUN_GATLIN] == false)
			if(money >= dollars[GUN_GATLIN])
			{
				upgrades[GUN_GATLIN] = true;
				SetMoney( -dollars[GUN_GATLIN]);
			}
	if(GetKeyState(0x36) & 0x80)	//6
		if(upgrades[GUN_GATLIN] == true && upgrades[GUN_PROTO] == false)
			if(money >= dollars[GUN_PROTO])
			{
				upgrades[GUN_PROTO] = true;
				SetMoney( -dollars[GUN_PROTO]);
			}

	if(GetKeyState(0x37) & 0x80)	//7
	{
		if(upgrades[GUN_POINT] == false)
			if(money >= dollars[GUN_POINT])
			{
				upgrades[GUN_POINT] = true;
				SetMoney( -dollars[GUN_POINT]);
			}
	}
	if(GetKeyState(0x38) & 0x80)	//8
		if(upgrades[THRUSTER_TYPED] == false)
			if(money >= dollars[THRUSTER_TYPED])
			{
				upgrades[THRUSTER_TYPED] = true;
				SetMoney(-500);
			}
	if(GetKeyState(0x39) & 0x80)	//9
		if(upgrades[THRUSTER_TYPED] == true && upgrades[THRUSTER_MARKI] == false)
			if(money >= 1500)
			{
				upgrades[THRUSTER_MARKI] = true;
				SetMoney( -dollars[THRUSTER_TYPED]);
			}

	if(GetKeyState(0x45) & 0x80)	//E
	{
		if(upgrades[THRUSTER_TYPED] == false)		
			upgrades[THRUSTER_TYPED] = true;
		else if(upgrades[THRUSTER_MARKI] == false)
			upgrades[THRUSTER_MARKI] = true;
	}
}
void Market::render()
{
	//Initial RECTs
	RECT font_rect;
	font_rect.top = 0;
	font_rect.left = 0;
	font_rect.bottom = 600;
	font_rect.right = 800;

	RECT BG;
	BG.top = 0;
	BG.left = 0;
	BG.bottom = 720;
	BG.right = 1280;
	//Market Keyboard
	keyboard();

	//Sprite Background
	D3DXVECTOR3 pos;
	pos.x=-500.0f;
	pos.y=-50.0f;
	pos.z=0.0f;

	hanger->Begin(D3DXSPRITE_ALPHABLEND);
	hanger->Draw(pTexture,NULL,NULL,&pos,0xFFFFFFFF);
	hanger->End();





	//Set Variables
	bool* UPS = getUpgrades();
	int dollar = GetMoney();
	int* cost = GetDollars();


	//CENTER TITLE
	font_rect.top=15;
    p_font_title->DrawText(NULL, "ACME CORPORATION",-1,&font_rect,DT_CENTER,0xBB44AFDF);
//===================================================================================================================================
//		LEFT COLUMN
//===================================================================================================================================
	//Shield Upgrades:
	font_rect.top=68;
	font_rect.left=75;
    p_font_subtitle->DrawText(NULL, "Shield Upgrades:",-1,&font_rect,DT_LEFT,0xBB44AFDF);
		font_rect.left=100;
		//SHIELD_AMP
		font_rect.top = 102;
		if(UPS[SHIELD_AMP])
			p_font_text->DrawText(NULL, "Shield Boost Amplifier I",-1,&font_rect,DT_LEFT,0xBB885500);
		else if( UPS[GEN_TYPED] == false || dollar < cost[SHIELD_AMP])		//grey text when cannot upgrade
			p_font_text->DrawText(NULL, "Shield Boost Amplifier I (requires TYPE-D Gen.)",-1,&font_rect,DT_LEFT,0xBB666666);
		else if( UPS[GEN_TYPED] == true && dollar >= cost[SHIELD_AMP] )
			p_font_text->DrawText(NULL, "Shield Boost Amplifier I",-1,&font_rect,DT_LEFT,0xBBFFCC00);
		//SHIELD_PROTO
		font_rect.top = 132;
		if(UPS[SHIELD_PROTO])
			p_font_text->DrawText(NULL, "5A Prototype Shield Support",-1,&font_rect,DT_LEFT,0xBB885500);
		else if(UPS[GEN_TYPEE] == false || dollar < cost[SHIELD_PROTO])		//grey text when cannot upgrade
			p_font_text->DrawText(NULL, "5A Prototype Shield Support (Requires TYPE-E Gen.)",-1,&font_rect,DT_LEFT,0xBB666666);
		else if(UPS[GEN_TYPEE] == true && dollar >= cost[SHIELD_PROTO])	
			p_font_text->DrawText(NULL, "5A Prototype Shield Support",-1,&font_rect,DT_LEFT,0xBBFFCC00);
	//Generator Upgrades:
	font_rect.top=162;
	font_rect.left=75;
    p_font_subtitle->DrawText(NULL, "Generator Upgrades:",-1,&font_rect,DT_LEFT,0xBB44AFDF);
		font_rect.left=100;
		//GEN_TYPED
		font_rect.top = 196;
		if(UPS[GEN_TYPED])
			p_font_text->DrawText(NULL, "Type-D Power Core Modification",-1,&font_rect,DT_LEFT,0xBB885500);
		else if(dollar < cost[GEN_TYPED])		//grey text when cannot upgrade
			p_font_text->DrawText(NULL, "Type-D Power Core Modification",-1,&font_rect,DT_LEFT,0xBB666666);
		else if(dollar >= cost[GEN_TYPED])
			p_font_text->DrawText(NULL, "Type-D Power Core Modification",-1,&font_rect,DT_LEFT,0xBBFFCC00);
		//GEN_TYPEE
		font_rect.top = 226;
		if(UPS[GEN_TYPEE])
			p_font_text->DrawText(NULL, "Type-E Power Core Modification",-1,&font_rect,DT_LEFT,0xBB885500);
		else if(UPS[GEN_TYPED] == false || money < cost[GEN_TYPEE])		//grey text when cannot upgrade
			p_font_text->DrawText(NULL, "Type-E Power Core Modification (Requires TYPE-D Gen.)",-1,&font_rect,DT_LEFT,0xBB666666);
		else if(UPS[GEN_TYPED] == true && money >= cost[GEN_TYPEE])
			p_font_text->DrawText(NULL, "Type-E Power Core Modification",-1,&font_rect,DT_LEFT,0xBBFFCC00);
	//Cannon Upgrades:
	font_rect.top=256;
	font_rect.left=75;
    p_font_subtitle->DrawText(NULL, "Cannon Upgrades:",-1,&font_rect,DT_LEFT,0xBB44AFDF);
		font_rect.left=100;
		//GUN_GATLIN
		font_rect.top=290;
		if(UPS[GUN_GATLIN])
			p_font_text->DrawText(NULL, "75mm Gatling Rail I",-1,&font_rect,DT_LEFT,0xBB885500);
		else if(dollar < cost[GUN_GATLIN])		//grey text when cannot upgrade
			p_font_text->DrawText(NULL, "75mm Gatling Rail I",-1,&font_rect,DT_LEFT,0xBB666666);
		else if(dollar >= cost[GUN_GATLIN])
			p_font_text->DrawText(NULL, "75mm Gatling Rail I",-1,&font_rect,DT_LEFT,0xBBFFCC00);
		//GUN_PROTO
		font_rect.top=320;
		if(UPS[GUN_PROTO])
			p_font_text->DrawText(NULL, "75mm Prototype I Gauss Gun",-1,&font_rect,DT_LEFT,0xBB885500);
		else if(UPS[GUN_GATLIN] == false || dollar < cost[GUN_PROTO])		//grey text when cannot upgrade
			p_font_text->DrawText(NULL, "75mm Prototype I Gauss Gun (Requires gatlin upgrade)",-1,&font_rect,DT_LEFT,0xBB666666);
		else if(UPS[GUN_GATLIN] == true && dollar >= cost[GUN_PROTO])
			p_font_text->DrawText(NULL, "75mm Prototype I Gauss Gun",-1,&font_rect,DT_LEFT,0xBBFFCC00);
		//GUN_POINT
		font_rect.top=350;
		if( UPS[GUN_POINT])
			p_font_text->DrawText(NULL, "Partial Weapon Navigation",-1,&font_rect,DT_LEFT,0xBB885500);
		else if( dollar < cost[GUN_POINT] )		//grey text when cannot upgrade
			p_font_text->DrawText(NULL, "Partial Weapon Navigation",-1,&font_rect,DT_LEFT,0xBB666666);
		else if( dollar >= cost[GUN_POINT] )
			p_font_text->DrawText(NULL, "Partial Weapon Navigation",-1,&font_rect,DT_LEFT,0xBBFFCC00);
	//Thruster Upgrades:
	font_rect.top=380;
	font_rect.left=75;
    p_font_subtitle->DrawText(NULL, "Thruster Upgrades:",-1,&font_rect,DT_LEFT,0xBB44AFDF);
		font_rect.left=100;
		//THRUSTER_TYPED
		font_rect.top=414;
		if( UPS[THRUSTER_TYPED])
			p_font_text->DrawText(NULL, "Type-D Altered SS Overdrive",-1,&font_rect,DT_LEFT,0xBB885500);
		else if( dollar < cost[THRUSTER_TYPED] )		//grey text when cannot upgrade
			p_font_text->DrawText(NULL, "Type-D Altered SS Overdrive",-1,&font_rect,DT_LEFT,0xBB666666);
		else if( dollar >= cost[THRUSTER_TYPED] )
			p_font_text->DrawText(NULL, "Type-D Altered SS Overdrive",-1,&font_rect,DT_LEFT,0xBBFFCC00);
		//THRUSTER_MARKI
		font_rect.top=444;
		if(UPS[THRUSTER_MARKI])
			p_font_text->DrawText(NULL, "Mark I Modified SS Inertial Stabilizers",-1,&font_rect,DT_LEFT,0xBB885500);
		else if( dollar < cost[THRUSTER_MARKI] )		//grey text when cannot upgrade
			p_font_text->DrawText(NULL, "Mark I Modified SS Inertial Stabilizers",-1,&font_rect,DT_LEFT,0xBB666666);
		else if( dollar >= cost[THRUSTER_MARKI] )
			p_font_text->DrawText(NULL, "Mark I Modified SS Inertial Stabilizers",-1,&font_rect,DT_LEFT,0xBBFFCC00);
	
//===================================================================================================================================
//		RIGHT COLUMN
//===================================================================================================================================
	//Set the dollar value to wstring
	stringstream str_dollars[12];
	str_dollars[SHIELD_AMP] << dollars[SHIELD_AMP];
	str_dollars[SHIELD_PROTO] << dollars[SHIELD_PROTO];
	str_dollars[GEN_TYPED] << dollars[GEN_TYPED];
	str_dollars[GEN_TYPEE] << dollars[GEN_TYPEE];
	str_dollars[GUN_GATLIN] << dollars[GUN_GATLIN];
	str_dollars[GUN_PROTO] << dollars[GUN_PROTO];
	str_dollars[GUN_POINT] << dollars[GUN_POINT];
	str_dollars[THRUSTER_TYPED] << dollars[THRUSTER_TYPED];
	str_dollars[THRUSTER_MARKI] << dollars[THRUSTER_MARKI];
		
		
		
	font_rect.right=700;
	//Shield Upgrades:
		//SHIELD_AMP
		font_rect.top = 102;
		if(UPS[SHIELD_AMP])
			p_font_text->DrawText(NULL, "Purchased",-1,&font_rect,DT_RIGHT,0xBB885500);
		else if( UPS[GEN_TYPED] == false || dollar < cost[SHIELD_AMP])		//grey text when cannot upgrade
			p_font_text->DrawText(NULL, "Locked",-1,&font_rect,DT_RIGHT,0xBB666666);
		else if( UPS[GEN_TYPED] == true && dollar >= cost[SHIELD_AMP] )
			p_font_text->DrawText(NULL, str_dollars[SHIELD_AMP].str().c_str(),-1,&font_rect,DT_RIGHT,0xBBFFCC00);
		//SHIELD_PROTO
		font_rect.top = 132;
		if(UPS[SHIELD_PROTO])
			p_font_text->DrawText(NULL, "Purchased",-1,&font_rect,DT_RIGHT,0xBB885500);
		else if(UPS[GEN_TYPEE] == false || dollar < cost[SHIELD_PROTO])		//grey text when cannot upgrade
			p_font_text->DrawText(NULL, "Locked",-1,&font_rect,DT_RIGHT,0xBB666666);
		else if(UPS[GEN_TYPEE] == true && dollar >= cost[SHIELD_PROTO])	
			p_font_text->DrawText(NULL, str_dollars[SHIELD_PROTO].str().c_str(),-1,&font_rect,DT_RIGHT,0xBBFFCC00);
	//Generator Upgrades:
		//GEN_TYPED
		font_rect.top = 196;
		if(UPS[GEN_TYPED])
			p_font_text->DrawText(NULL, "Purchased",-1,&font_rect,DT_RIGHT,0xBB885500);
		else if(dollar < cost[GEN_TYPED])		//grey text when cannot upgrade
			p_font_text->DrawText(NULL, "Locked",-1,&font_rect,DT_RIGHT,0xBB666666);
		else if(dollar >= cost[GEN_TYPED])
			p_font_text->DrawText(NULL, str_dollars[GEN_TYPED].str().c_str(),-1,&font_rect,DT_RIGHT,0xBBFFCC00);
		//GEN_TYPEE
		font_rect.top = 226;
		if(UPS[GEN_TYPEE])
			p_font_text->DrawText(NULL, "Purchased",-1,&font_rect,DT_RIGHT,0xBB885500);
		else if(UPS[GEN_TYPED] == false || money < cost[GEN_TYPEE])		//grey text when cannot upgrade
			p_font_text->DrawText(NULL, "Locked",-1,&font_rect,DT_RIGHT,0xBB666666);
		else if(UPS[GEN_TYPED] == true && money >= cost[GEN_TYPEE])
			p_font_text->DrawText(NULL, str_dollars[GEN_TYPEE].str().c_str(),-1,&font_rect,DT_RIGHT,0xBBFFCC00);
	//Cannon Upgrades:
		//GUN_GATLIN
		font_rect.top=290;
		if(UPS[GUN_GATLIN])
			p_font_text->DrawText(NULL, "Purchased",-1,&font_rect,DT_RIGHT,0xBB885500);
		else if(dollar < cost[GUN_GATLIN])		//grey text when cannot upgrade
			p_font_text->DrawText(NULL, "Locked",-1,&font_rect,DT_RIGHT,0xBB666666);
		else if(dollar >= cost[GUN_GATLIN])
			p_font_text->DrawText(NULL, str_dollars[GUN_GATLIN].str().c_str(),-1,&font_rect,DT_RIGHT,0xBBFFCC00);
		//GUN_PROTO
		font_rect.top=320;
		if(UPS[GUN_PROTO])
			p_font_text->DrawText(NULL, "Purchased",-1,&font_rect,DT_RIGHT,0xBB885500);
		else if(UPS[GUN_GATLIN] == false || dollar < cost[GUN_PROTO])		//grey text when cannot upgrade
			p_font_text->DrawText(NULL, "Locked",-1,&font_rect,DT_RIGHT,0xBB666666);
		else if(UPS[GUN_GATLIN] == true && dollar >= cost[GUN_PROTO])
			p_font_text->DrawText(NULL, str_dollars[GUN_PROTO].str().c_str(),-1,&font_rect,DT_RIGHT,0xBBFFCC00);
		//GUN_POINT
		font_rect.top=350;
		if( UPS[GUN_POINT])
			p_font_text->DrawText(NULL, "Purchased",-1,&font_rect,DT_RIGHT,0xBB885500);
		else if( dollar < cost[GUN_POINT] )		//grey text when cannot upgrade
			p_font_text->DrawText(NULL, "Locked",-1,&font_rect,DT_RIGHT,0xBB666666);
		else if( dollar >= cost[GUN_POINT] )
			p_font_text->DrawText(NULL, str_dollars[GUN_POINT].str().c_str(),-1,&font_rect,DT_RIGHT,0xBBFFCC00);
	//Thruster Upgrades:
		//THRUSTER_TYPED
		font_rect.top=414;
		if( UPS[THRUSTER_TYPED])
			p_font_text->DrawText(NULL, "Purchased",-1,&font_rect,DT_RIGHT,0xBB885500);
		else if( dollar < cost[THRUSTER_TYPED] )		//grey text when cannot upgrade
			p_font_text->DrawText(NULL, "Locked",-1,&font_rect,DT_RIGHT,0xBB666666);
		else if( dollar >= cost[THRUSTER_TYPED] )
			p_font_text->DrawText(NULL, str_dollars[THRUSTER_TYPED].str().c_str(),-1,&font_rect,DT_RIGHT,0xBBFFCC00);
		//THRUSTER_MARKI
		font_rect.top=444;
		if(UPS[THRUSTER_MARKI])
			p_font_text->DrawText(NULL, "Purchased",-1,&font_rect,DT_RIGHT,0xBB885500);
		else if( dollar < cost[THRUSTER_MARKI] )		//grey text when cannot upgrade
			p_font_text->DrawText(NULL, "Locked",-1,&font_rect,DT_RIGHT,0xBB666666);
		else if( dollar >= cost[THRUSTER_MARKI] )
			p_font_text->DrawText(NULL, str_dollars[THRUSTER_MARKI].str().c_str(),-1,&font_rect,DT_RIGHT,0xBBFFCC00);
}

//Shield Upgrades:
	//Shield Boost Amplifier I
void Market::setShieldAmp()
{

}
	//5A Prototype Shield Support
void Market::ShieldProto()
{
	graphics.EFFECTS_UpgradeToShieldProto();
}
//Generator Upgrades:
	//Type-D Power Core Modification
void Market::setGenTypeD()
{
	graphics.EFFECTS_UpgradeToGenTypeD();
	graphics.HUD_UpgradeToGenTypeE();
}
	//Type-E Power Core Modification
void Market::setGenTypeE()
{
	graphics.EFFECTS_UpgradeToGenTypeE();
	graphics.HUD_UpgradeToGenTypeE();
}
//Cannon Upgrades:
	//75mm Gatling Rail I
void Market::setGunGatlin()
{
	graphics.EFFECTS_UpgradeToGunGatlin();
}
	//75mm Prototype I Gauss Gun
void Market::setGunProto()
{
	graphics.EFFECTS_UpgradeToGunProto();
}
	//Partial Weapon Navigation
void Market::setGunPoint()
{
	graphics.EFFECTS_UpgradeToGunPoint();
}
//Thruster Upgrades:
	//Type-D Altered SS Overdrive
void Market::setThrusterTypeD()
{
	graphics.EFFECTS_UpgradeToThrusterTypeD();
}
	//Mark I Modified SS Inertial Stabilizers
void Market::setThrusterMarkI()
{
	graphics.EFFECTS_UpgradeToThrusterMarkI();
}