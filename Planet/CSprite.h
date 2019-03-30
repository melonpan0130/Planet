#pragma once
class CSprite
{
protected:
	LPDIRECT3DDEVICE9 m_pD3DDevice;
	LPD3DXSPRITE m_pSpr;
	LPDIRECT3DTEXTURE9 m_pTexture;

	D3DXVECTOR3 m_Pos;
	D3DXVECTOR3 m_Center;
	D3DCOLOR m_Color;

public:
	CSprite(LPDIRECT3DDEVICE9 pD3DDevice
		, LPDIRECT3DTEXTURE9 pTexture
		, const D3DXVECTOR3& Center);
	virtual ~CSprite();

	void InitSprite();
	void Release();

	void SetPositioin(const D3DXVECTOR3& pos)
	{
		m_Pos = pos;
	}
	void SetTexture(LPDIRECT3DTEXTURE9 pTexture)
	{
		m_pTexture = pTexture;
	}

	void Draw();
};

