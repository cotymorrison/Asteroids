#include "Shader.h"
#include "Graphics.h"

extern Graphics graphics;

#define dwShaderFlags D3DXFX_NOT_CLONEABLE | D3DXSHADER_DEBUG | D3DXSHADER_NO_PRESHADER

void Shader::Init()
{
	LPD3DXBUFFER buff;
	LPDIRECT3DDEVICE9 device = graphics.getDevice();
	string err;

	D3DXCreateEffectFromFile( graphics.getDevice(), "Specular.fx", NULL, NULL, dwShaderFlags, NULL, &SpecEffect, &buff );

	if(buff)
		err = string(reinterpret_cast<char*>(buff->GetBufferPointer()));

	D3DXCreateEffectFromFile( graphics.getDevice(), "Bump.fx", NULL, NULL, dwShaderFlags, NULL, &BumpEffect, &buff );
	
	if(buff)
		err = string(reinterpret_cast<char*>(buff->GetBufferPointer()));	
}

void Shader::specular(D3DXMATRIX *Model, LPD3DXMESH mesh, LPDIRECT3DTEXTURE9 texture, DWORD numMaterials)
{
 //   D3DXMATRIX ModelViewProj = *Model * graphics.getView() * graphics.getProj();
	//D3DXVECTOR3 temp = graphics.getLightVector();
	//D3DXVECTOR4 LightVec = D3DXVECTOR4(temp.x, temp.y, temp.z, 1.0f);

	//D3DXMATRIX ModelViewIT = *Model * graphics.getView();
	//D3DXMatrixInverse(&ModelViewIT, NULL, &ModelViewIT);
	//D3DXMatrixTranspose(&ModelViewIT, &ModelViewIT);
	//
 //   SpecEffect->SetTexture( "MeshTexture", texture );

 //   SpecEffect->SetValue( "LightVec", LightVec, sizeof(LightVec) );

 //   // Update the effect's variables.  Instead of using strings, it would 
 //   // be more efficient to cache a handle to the parameter by calling 
 //   // ID3DXEffect::GetParameterByName

 //   SpecEffect->SetMatrix( "ModelViewProj", &ModelViewProj );

 //   SpecEffect->SetMatrix( "ModelViewIT", &ModelViewIT );

 //   // Render the scene with this technique 
 //   // as defined in the .fx file
 //   SpecEffect->SetTechnique( "RenderScene" );

	//UINT iPass, cPasses;

 //   // Apply the technique contained in the effect 
 //   SpecEffect->Begin( &cPasses, 0 );

 //   for( iPass = 0; iPass < cPasses; iPass++ )
 //   {
 //       SpecEffect->BeginPass( iPass );

 //       // Render the mesh with the applied technique
	//	for (int i=0; i<numMaterials; i++)
	//		mesh->DrawSubset( i );

 //       // The effect interface queues up the changes and performs them 
 //       // with the CommitChanges call. You do not need to call CommitChanges if 
 //       // you are not setting any parameters between the BeginPass and EndPass.
 //       // V( g_pEffect->CommitChanges() );


 //       SpecEffect->EndPass();
 //   }
 //   SpecEffect->End();
}

void Shader::bump(D3DXMATRIX *Model, D3DMATERIAL9 material, LPD3DXMESH mesh, LPDIRECT3DTEXTURE9 texture, LPDIRECT3DTEXTURE9 bump_map, DWORD numMaterials)
{
    D3DXMATRIX ModelView = *Model * graphics.getView();
    D3DXMATRIX ModelViewProj = *Model * graphics.getView() * graphics.getProj();
	//D3DXVECTOR3 temp = graphics.getLightVector();
	D3DXVECTOR4 vLight = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f);

	/*D3DXVec4Transform( &vLight, &vLight, &graphics.LEVEL_getWorld() );
    D3DXVec4Transform( &vLight, &vLight, &graphics.GetView() );*/

	//D3DXMATRIX ModelViewIT = *Model * graphics.getView();
	//D3DXMatrixInverse(&ModelViewIT, NULL, &ModelViewIT);
	//D3DXMatrixTranspose(&ModelViewIT, &ModelViewIT);

	D3DXVECTOR4 vEye = D3DXVECTOR4(graphics.getCamPos());
	vEye.w = 0.0f;

    //D3DXVec4Transform( &vEye, &vEye, &graphics.LEVEL_getWorld() );
    //D3DXVec4Transform( &vEye, &vEye, &graphics.GetView() );

	D3DCOLORVALUE diffuse  = {0.5, 0.5, 0.5, 0.0};//material.Diffuse;  //RGBA
    D3DCOLORVALUE specular = {0.5, 0.5, 1.0, 0.0};//material.Specular;
	D3DCOLORVALUE ambient  = {0.5, 0.5, 0.5, 0.0};//material.Ambient;

	float power = 32.0f;

	D3DXVec4Transform( &vLight, &vLight, &graphics.getView() );


	BumpEffect->SetMatrix( "ModelWorld", Model );
	BumpEffect->SetMatrix( "ModelView", &ModelView );
	BumpEffect->SetMatrix( "ModelViewProj", &ModelViewProj );
	BumpEffect->SetValue( "vLight", &vLight, sizeof(vLight) );
	BumpEffect->SetValue( "vEye", &vEye, sizeof(vEye) );
	BumpEffect->SetValue( "vDiffuseMaterial", &diffuse, sizeof(diffuse) );
	BumpEffect->SetValue( "vSpecularMaterial", &specular, sizeof(specular) );
	BumpEffect->SetValue( "vAmbient", &ambient, sizeof(ambient) );
	BumpEffect->SetValue( "power", &power, sizeof(power) );

	BumpEffect->SetTexture( "MeshTexture", texture );
	BumpEffect->SetTexture( "BumpTexture", bump_map );

    // Update the effect's variables.  Instead of using strings, it would 
    // be more efficient to cache a handle to the parameter by calling 
    // ID3DXEffect::GetParameterByName

    // Render the scene with this technique 
    // as defined in the .fx file
    BumpEffect->SetTechnique( "RenderScene" );

	UINT iPass, cPasses;

    // Apply the technique contained in the effect 
    BumpEffect->Begin( &cPasses, 0 );

    for( iPass = 0; iPass < cPasses; iPass++ )
    {
        BumpEffect->BeginPass( iPass );

        // Render the mesh with the applied technique
		for (int i=0; i<numMaterials; i++)
			mesh->DrawSubset( i );

        // The effect interface queues up the changes and performs them 
        // with the CommitChanges call. You do not need to call CommitChanges if 
        // you are not setting any parameters between the BeginPass and EndPass.
        // V( g_pEffect->CommitChanges() );


        BumpEffect->EndPass();
    }
    BumpEffect->End();
}