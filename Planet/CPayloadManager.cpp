#include "stdafx.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "CSprite.h"
#include "CPayload.h"
#include "CPayloadManager.h"


CPayloadManager::CPayloadManager(LPDIRECT3DDEVICE9 pD3DDevice
	, LPDIRECT3DTEXTURE9 texture
	, const D3DXVECTOR3 & center
	, float speed
	, const D3DXVECTOR3 & dir
	, const D3DXVECTOR2 & screensize)
{
	for (int i = 0; i < PAYLOAD_MAX; i++)
	{
		m_Payload[i] = new CPayload(pD3DDevice
			, texture, center, speed, dir, screensize);
	}
}

CPayloadManager::~CPayloadManager()
{
	for (int i = 0; i < PAYLOAD_MAX; i++)
		delete m_Payload[i];
}

int CPayloadManager::getEmptyPayload()
{
	for (int i = 0; i < PAYLOAD_MAX; i++)
		if (m_Payload[i]->IsAlive() == false)
			return i;
	return -1;
}

void CPayloadManager::Update(float dt)
{
	for (int i = 0; i < PAYLOAD_MAX; i++)
			m_Payload[i]->Update(dt);
}

void CPayloadManager::Draw()
{
	for (int i = 0; i < PAYLOAD_MAX; i++)
			m_Payload[i]->Draw();
}

void CPayloadManager::OnFire(const D3DXVECTOR3 & pos)
{
	int id = getEmptyPayload();
	if (id != -1)
	{
		m_Payload[id]->OnFire(pos);
	}
}

void CPayloadManager::OnFire(const D3DXVECTOR3 & pos, const D3DXVECTOR3 & dir)
{
	int id = getEmptyPayload();
	if (id != -1)
	{
		m_Payload[id]->OnFire(pos, dir);
	}
}

void CPayloadManager::OnFire3(const D3DXVECTOR3 & pos)
{
	int id = getEmptyPayload();
	if (id != -1)
	{
		m_Payload[id]->OnFire(pos + D3DXVECTOR3(-30, 0, 0));
		m_Payload[id]->SetDir(D3DXVECTOR3(-0.5, -0.7, 0));
	}

	id = getEmptyPayload();
	if (id != -1)
	{
		m_Payload[id]->OnFire(pos + D3DXVECTOR3(30, 0, 0));
		m_Payload[id]->SetDir(D3DXVECTOR3(0.5, -0.7, 0));
	}

	id = getEmptyPayload();
	if (id != -1)
	{
		m_Payload[id]->OnFire(pos);
		m_Payload[id]->SetDir(D3DXVECTOR3(0, -1, 0));
	}
}

void CPayloadManager::OnHoming(const D3DXVECTOR3 & pos
	, const D3DXVECTOR3& target)
{
	int id = getEmptyPayload();
	D3DXVECTOR3 dir = target - pos;
	m_Payload[id]->OnFire(pos, dir);
	static int homingIndex = -1;
	homing[++homingIndex] = id;
}

void CPayloadManager::HomingUpdate(float dt
	, const D3DXVECTOR3& target)
{
	D3DXVECTOR3 dir;
	
	for (int a : homing)
	{
		if (a != -1 && m_Payload[a]->IsAlive() == true)
		{
			m_Payload[a]->GetPos();
			dir = target - m_Payload[a]->GetPos();
			m_Payload[a]->SetDir(dir);
		}
	}
}

bool CPayloadManager::IsCollision(const D3DXVECTOR3 & pos, float radious)
{
	for(int i=0;i<PAYLOAD_MAX;i++)
		if (m_Payload[i]->IsAlive())
		{
			D3DXVECTOR3 dist = m_Payload[i]->GetPos() - pos;
			if (D3DXVec3Length(&dist) < radious)
			{
				m_Payload[i]->SetAlive(false);
				return true;
			}
		}
	return false;
}
