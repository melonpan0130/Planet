#pragma once
class CGameObject;

class CTrap
{
public:
	CTrap();
	CTrap(LPDIRECT3DDEVICE9 pD3DDevice
		, float speed, int type);

	virtual ~CTrap();

	void InitGameObject(LPDIRECT3DDEVICE9 pD3DDevice
		, LPDIRECT3DTEXTURE9 pTexture
		, const D3DXVECTOR3& position);
	void Release();

	void Update(float dt);
};

