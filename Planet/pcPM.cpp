#include "stdafx.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "CTexture.h"
#include "CPayloadManager.h"
#include "pcPM.h"

pcPM::pcPM(LPDIRECT3DDEVICE9 pD3DDevice)
{
	m_pD3DDevice = pD3DDevice;
	m_pTexture = new CTexture(m_pD3DDevice);
	
	normalMissile = NULL;
	homingMissile = NULL;
	threeMissile = NULL;
}

pcPM::~pcPM()
{
	delete normalMissile;
	delete homingMissile;
	delete threeMissile;

	delete m_pTexture;
	delete m_pD3DDevice;
}

void pcPM::InitPM(float m_ScreenWidth, float m_ScreenHeight)
{
	normalMissile = new CPayloadManager(m_pD3DDevice
		, m_pTexture->GetTexture(0)
		, D3DXVECTOR3(16.f, 16.f, 0.f)
		, 400.f
		, D3DXVECTOR3(0.f, -1.f, 0.f)
		, D3DXVECTOR2(m_ScreenWidth, m_ScreenHeight));

	homingMissile = new CPayloadManager(m_pD3DDevice
		, m_pTexture->GetTexture(1)
		, D3DXVECTOR3(32.f, 32.f, 0)
		, 400.f
		, D3DXVECTOR3(0.f, -1.f, 0.f)
		, D3DXVECTOR2(m_ScreenWidth, m_ScreenHeight));

	threeMissile=new CPayloadManager(m_pD3DDevice
		, m_pTexture->GetTexture(0)
		, D3DXVECTOR3(16.f, 16.f, 0.f)
		, 400.f
		, D3DXVECTOR3(0.f, -1.f, 0.f)
		, D3DXVECTOR2(m_ScreenWidth, m_ScreenHeight));
}

void pcPM::Update(float dt)
{
	normalMissile->Update(dt);
	homingMissile->Update(dt);
}

void pcPM::Draw()
{
	normalMissile->Draw();
	homingMissile->Draw();
}

void pcPM::normalOnfire(const D3DXVECTOR3 & pos)
{
	normalMissile->OnFire(pos);
}

void pcPM::homingOnfire(const D3DXVECTOR3 & pos)
{
	homingMissile->OnFire(pos);
}

void pcPM::LoadTextures()
{
	m_pTexture->LoadTexture(-1, TEXT("../img/fire.png"));
	m_pTexture->LoadTexture(-1, TEXT("../img/missle.png"));
}
