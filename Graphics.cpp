#include "Graphics.h"
#include "DirectInput.h"
extern DirectInput mouse;

#define MULTISAMPLE_TYPE D3DMULTISAMPLE_4_SAMPLES

Graphics::Graphics()
{
    pD3D = NULL;
    pDevice = NULL;
	srand( timeGetTime() );
}
    
HRESULT Graphics::initialize( HINSTANCE hInst, HWND hWnd )
{
    // Create the D3D object.
    if( NULL == ( pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
        return E_FAIL;

    // Set up the structure used to create the D3DDevice. Since we are now
    // using more complex geometry, we will create a device with a zbuffer.

    ZeroMemory( &d3dpp, sizeof( d3dpp ) );
    d3dpp.Windowed = TRUE;
	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.BackBufferCount		 = 1;
    d3dpp.EnableAutoDepthStencil = TRUE;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.hDeviceWindow = hWnd;

	if( SUCCEEDED(pD3D->CheckDeviceMultiSampleType( D3DADAPTER_DEFAULT , 
                                D3DDEVTYPE_HAL, d3dpp.BackBufferFormat, 
                                FALSE, MULTISAMPLE_TYPE, NULL ) ) )
		d3dpp.MultiSampleType = MULTISAMPLE_TYPE;


    // Create the D3DDevice
    if( FAILED( pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
                                      D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                      &d3dpp, &pDevice ) ) )
        return E_FAIL;


    // Turn on the zbuffer
    pDevice->SetRenderState(D3DRS_ZENABLE, TRUE );
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	
	// Turn off lighting
	pDevice->SetRenderState(D3DRS_LIGHTING,FALSE);

	//FPS font
//	D3DXCreateFont( pDevice,
//					40,
//					0,
//					FW_BOLD,
//					1,
//					FALSE,
//					DEFAULT_CHARSET,
//					OUT_DEFAULT_PRECIS,
//					ANTIALIASED_QUALITY,
//					DEFAULT_PITCH|FF_DONTCARE,
//					_T("Comic Sans MS"),
//					&font);


	shader.Init();
	hud.Initialize();
	effect.Initialize();
	level.Initialize(100);

	time = timeGetTime();

    return S_OK;
}

void Graphics::cleanup()
{
    SAFE_RELEASE( font );

    SAFE_RELEASE( pDevice );

    SAFE_RELEASE( pD3D );
}


LPDIRECT3DDEVICE9 Graphics::getDevice()
{
    return pDevice;
}

void Graphics::LEVEL_USER_update()
{
	//level.update(&user.getShipVelocity());

	level.CheckBounds();
	level.CheckShipBounds();
}

HRESULT Graphics::beginScene()
{
    // Clear the back buffer to black
	pDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,0,0), 1.0f, 0 );
	return pDevice->BeginScene();
}

void Graphics::render()
{
	last = time;
	time = timeGetTime();

	//temp mouse control ======================================================================================
	mouse.detect_input();    // update the input data before rendering


	LEVEL_USER_update();
	level.render();
	effect.render();
	hud.render();
}

void Graphics::ShadeSpec(D3DXMATRIX *model, LPD3DXMESH mesh, LPDIRECT3DTEXTURE9 texture, DWORD numMaterials)
{
	shader.specular(model, mesh, texture, numMaterials);
}

void Graphics::ShadeBump(D3DXMATRIX *model, D3DMATERIAL9 material, LPD3DXMESH mesh, LPDIRECT3DTEXTURE9 texture, LPDIRECT3DTEXTURE9 bump_map, DWORD numMaterials)
{
	shader.bump(model, material, mesh, texture, bump_map, numMaterials);
}

HRESULT Graphics::endScene()
{
    pDevice->EndScene();
	
	// Display rendered scene
	return pDevice->Present( NULL, NULL, NULL, NULL );
}

float Graphics::getTimeDifference()
{
	return float(time - last)/1000;
}

float Graphics::getFPS()
{
	float temp = getTimeDifference();

	if(temp != 0)
		return 1/temp;
	else
		return 0.0000001;
}

void Graphics::displayFPS()
{
	RECT rect = {0,0,800,600};

	stringstream fps;
	fps << "FPS: " << int(getFPS() + 0.5f);

	font->DrawText(NULL, fps.str().c_str(),-1,&rect,DT_LEFT,D3DCOLOR_XRGB(0,128,0));
}

void Graphics::PlaySound(LPSTR szFilename)
{
	if(!sound.isRunning())
		sound.PlaySound(szFilename);
}

void Graphics::setLight(Lights light, int pos)
{
	pDevice->SetLight(pos, &light.getLight() );
    pDevice->LightEnable(pos,TRUE);
    
    //pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	pDevice->SetRenderState(D3DRS_VERTEXBLEND, TRUE);
	//pDevice->SetRenderState(D3DRS_SPECULARENABLE, TRUE);
	//pDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
	//pDevice->SetRenderState(D3DRS_SPECULARMATERIALSOURCE, D3DMCS_MATERIAL);
    //pDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(0,0,0));
}
void Graphics::TurnOffLight(int pos)
{
    pDevice->LightEnable(pos,TRUE);
}
D3DXVECTOR3 Graphics::getLightVector()
{
	//D3DLIGHT9 light = lights.getLight();

	return D3DXVECTOR3(0.0, 1.0, 0.0);
}

D3DXMATRIX Graphics::getView()
{
	return view;
}

D3DXMATRIX Graphics::getProj()
{
	return projection;
}

//=============================================================================
//Get Ship Information for Level
//=============================================================================
D3DXMATRIX Graphics::getShipRotation()
{
	return level.getShipRotation();
}

D3DXVECTOR3 Graphics::getCrosshairPosition()
{
	return level.getCrosshairPosition();
}

void Graphics::updateWorld()
{
	world = level.getShipRotation();
}

void Graphics::setCamera(float x, float y, float z)
{
	camPos = D3DXVECTOR3(x, y, z);
    // [1] D3DTS_VIEW
    pDevice->SetTransform( D3DTS_VIEW, D3DXMatrixLookAtLH(&view, &D3DXVECTOR3(x,y,z),
                                                                  &D3DXVECTOR3(0,10,0), 
                                                                 &D3DXVECTOR3(0,1,0)));
}

D3DXVECTOR3 Graphics::getCamPos()
{
	return camPos;
}

void Graphics::setProjection( int width, int height )
{ 
    // [2] D3DTS_PROJECTION
    pDevice->SetTransform( D3DTS_PROJECTION, D3DXMatrixPerspectiveFovLH( &projection,  
		                        D3DX_PI/4,  ((float)width)/height, 1.0f, 1000.0f));
}

void Graphics::setMaterial()
{
      D3DMATERIAL9 material;
      
      D3DCOLORVALUE diffuse  = {1.0, 1.0, 1.0, 0.0};  //RGBA
      D3DCOLORVALUE ambient  = {1.0, 1.0, 1.0, 0.0};
      D3DCOLORVALUE specular = {1.0, 1.0, 1.0, 0.0};
      // emissive is for a glow effect
      D3DCOLORVALUE emissive = {0.0, 0.0, 0.0, 0.0};

      material.Diffuse = diffuse;
      material.Ambient = ambient;
      material.Specular = specular;
      material.Emissive = emissive;
      material.Power = 100.0f;

      pDevice->SetMaterial(&material);
}

D3DXMATRIX Graphics::GetView()
{
	return view;
}
bool* Graphics::getUpgrades()
{
	return level.getUpgrades();
}
D3DXVECTOR3 Graphics::getShipVelocity()
{
	return level.getShipVelocity();
}
void Graphics::setShipVelocity( const D3DXVECTOR3 newVelocity)
{
	level.setShipVelocity(newVelocity);
}
//=====================================================================================
//Level Linkage
//=====================================================================================
D3DXMATRIX Graphics::LEVEL_getLevelRotation()
{
	return level.getLevelRotation();
}

list<Asteroid>* Graphics::LEVEL_getAsteroids()
{
	return level.getAsteroids();
}

list<Asteroid>::iterator Graphics::LEVEL_Split(list<Asteroid>::iterator &it)
{
	return level.Split(it);
}

//=====================================================================================
//Hud Linkage
//=====================================================================================
bool Graphics::HUD_EnergyStateMax()
{
	return hud.EnergyStateMax();	
}
bool Graphics::HUD_EnergyStateMin()
{
	return hud.EnergyStateMin();	
}
void Graphics::HUD_AdjustEnergyLevel( const float consumption )
{
	hud.AdjustEnergyLevel( consumption );
}
bool Graphics::HUD_ShieldState()
{
	return hud.ShieldState();
}
void Graphics::HUD_SetShieldUse( bool use )
{
	hud.SetShieldUse( use );
}
bool Graphics::HUD_EnergyShieldStateMin()
{
	return hud.EnergyShieldStateMin();
}
void Graphics::HUD_UpgradeToGenTypeD()
{
	hud.UpgradeToGenTypeD();
}
void Graphics::HUD_UpgradeToGenTypeE()
{
	hud.UpgradeToGenTypeE();
}

//=====================================================================================
//User Linkage
//=====================================================================================
int Graphics::USER_getCurrentLives()
{
	return level.getCurrentLives();
}
int Graphics::USER_getCurrentScore()
{
	return level.getCurrentScore();
}
//=====================================================================================
//Effects Linkage
//=====================================================================================
//bool Graphics::EFFECTS_EnergyShieldStateMin()
//{
//	return effect.EnergyShieldStateMin();
//}
void Graphics::EFFECTS_UpgradeToGenTypeD()
{
	effect.UpgradeToGenTypeD();
}
void Graphics::EFFECTS_UpgradeToGenTypeE()
{
	effect.UpgradeToGenTypeE();
}
void Graphics::EFFECTS_UpgradeToShieldProto()
{
	effect.UpgradeToShieldProto();
}

void Graphics::EFFECTS_UpgradeToGunGatlin()
{
	effect.UpgradeToGunGatlin();
}
void Graphics::EFFECTS_UpgradeToGunProto()
{
	effect.UpgradeToGunProto();
}
void Graphics::EFFECTS_UpgradeToGunPoint()
{
	effect.UpgradeToGunPoint();
}
void Graphics::EFFECTS_UpgradeToThrusterTypeD()
{
	effect.UpgradeToThrusterTypeD();
}
void Graphics::EFFECTS_UpgradeToThrusterMarkI()
{
	effect.UpgradeToThrusterMarkI();
}
//============================================
float Graphics::EFFECTS_getThrusterDrainRate()
{
	return effect.getThrusterDrainRate();
}
void  Graphics::EFFECTS_renderAuxThrusterRight()
{
	effect.renderAuxThrusterRight();
}
void  Graphics::EFFECTS_renderAuxThrusterLeft()
{
	effect.renderAuxThrusterLeft();
}
void  Graphics::EFFECTS_renderThruster()
{
	effect.renderThruster();
}