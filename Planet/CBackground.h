#pragma once

class CTexture;
class CSprite;

class CBackground
{
public:
	explicit CBackground(LPDIRECT3DDEVICE9 pD3DDevice
		, LPDIRECT3DTEXTURE9 pTexture
		, D3DXVECTOR3 pos
		, float imgWidth
		, float speed);
	virtual ~CBackground();

	void Update(float dt);
	void Render();

	void SetScroll(float point)
	{
		m_Scroll = point;
		if (m_Scroll < -m_ImgWidth)
			m_Scroll += m_ImgWidth;
	}

protected:
	CSprite* m_Spr[3];

	D3DXVECTOR3 m_BasePos;
	float m_Scroll;
	float m_ImgWidth;
	float m_ScrollSpeed;
};

