#pragma once
class CPayloadManager;
class CTexture;

class pcPM
{
public:
	pcPM(LPDIRECT3DDEVICE9 pD3DDevice);
	virtual ~pcPM();

	void InitPM(float m_ScreenWidth, float m_ScreenHeight);

	void Update(float dt);
	void Draw();

	void normalOnfire(const D3DXVECTOR3 &pos);
	void homingOnfire(const D3DXVECTOR3 &pos);

	void LoadTextures(); // texture Á¢±Ù
	
protected:
	LPDIRECT3DDEVICE9 m_pD3DDevice;
	CPayloadManager* normalMissile;
	CPayloadManager* homingMissile;
	CPayloadManager* threeMissile;

	CTexture* m_pTexture;
};

