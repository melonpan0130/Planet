#pragma once
class CTexture;
class CSprite;

class CGameObject
{
public:
	CGameObject();
	CGameObject(LPDIRECT3DDEVICE9 pD3DDevice
		, LPDIRECT3DTEXTURE9 pTexture
		, const D3DXVECTOR3& center
		, const D3DXVECTOR3& position
		, float speed = 100.f);
	virtual ~CGameObject();

	void InitGameObject(LPDIRECT3DDEVICE9 pD3DDevice
		, LPDIRECT3DTEXTURE9 pTexture
		, const D3DXVECTOR3& center
		, const D3DXVECTOR3& position
		, float speed = 100.f);
	void Release();

	void Update(float dt);
	void Render();

	void ArrangePosition(float sx, float ex); // sprite가 화면밖에 넘어가지 않게;
	bool IsTouched(float leftX, float rightX, bool bUseRight);

	void SetPosition(D3DXVECTOR3 pos) { m_Pos = pos; }
	const D3DXVECTOR3& GetPosition() const { return m_Pos; }

	void SetDirection(float x, float y) { m_Dir = D3DXVECTOR3(x, y, 0.f); }
	const D3DXVECTOR3& GetDirection() const { return m_Dir; }

	void SetAlive(bool flag) { m_bAlive = flag; }
	bool GetAlive() { return m_bAlive; }

protected:
	CSprite* m_Spr;
	D3DXVECTOR3 m_Pos;
	D3DXVECTOR3 m_Center;
	D3DXVECTOR3 m_Dir;

	bool m_bAlive;
	float m_Speed;
};

