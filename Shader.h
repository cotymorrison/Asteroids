#pragma once

#include "Header.h"


class Shader
{
private:
	ID3DXEffect* SpecEffect;
	ID3DXEffect* BumpEffect;

public:
	void Init();
	void specular(D3DXMATRIX *Model, LPD3DXMESH mesh, LPDIRECT3DTEXTURE9 texture, DWORD numMaterials);
	void bump(D3DXMATRIX *Model, D3DMATERIAL9 material, LPD3DXMESH mesh, LPDIRECT3DTEXTURE9 texture, LPDIRECT3DTEXTURE9 bump_map, DWORD numMaterials);
};