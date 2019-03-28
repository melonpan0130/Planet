#include "stdafx.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "CTexture.h"
#include "CSprite.h"
#include "CBackground.h"

CBackground::CBackground(LPDIRECT3DDEVICE9 pD3DDevice
	, LPDIRECT3DTEXTURE9 pTexture
	, D3DXVECTOR3 pos
	, float imgWidth
	, float speed)
	: m_BasePos(pos)
	, m_ImgWidth(imgWidth)
	, m_ScrollSpeed(speed)
	, m_Scroll(0.1f)
{
	m_Spr[0] = new CSprite(pD3DDevice, pTexture, D3DXVECTOR3(0.f, 0.f, 0.f));
	m_Spr[1] = new CSprite(pD3DDevice, pTexture, D3DXVECTOR3(0.f, 0.f, 0.f));
	m_Spr[2] = new CSprite(pD3DDevice, pTexture, D3DXVECTOR3(0.f, 0.f, 0.f));
}

CBackground::~CBackground()
{
	for (int i = 0; i < 3; i++)
	{
		if (m_Spr[i] != NULL) 
		{
			delete m_Spr[i];
			m_Spr[i] = NULL;
		}
	}
}

void CBackground::Update(float dt)
{
	 m_Scroll -= (m_ScrollSpeed * dt);
	if (m_Scroll < -m_ImgWidth)
		m_Scroll += m_ImgWidth;

	D3DXVECTOR3 Pos1(m_Scroll, m_BasePos.y, 0.f);
	D3DXVECTOR3 Pos2 = Pos1 + D3DXVECTOR3(m_ImgWidth - 1.f, 0.f, 0.f); // ¿·¿¡ ¿¬°á
	D3DXVECTOR3 Pos3 = Pos2 + D3DXVECTOR3(m_ImgWidth - 1.f, 0.f, 0.f);

	m_Spr[0]->SetPositioin(Pos1);
	m_Spr[1]->SetPositioin(Pos2);
	m_Spr[2]->SetPositioin(Pos3);
}

void CBackground::Render()
{
	m_Spr[0]->Draw();
	m_Spr[1]->Draw();
	m_Spr[2]->Draw();
}