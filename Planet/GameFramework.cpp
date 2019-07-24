#include "stdafx.h"

#include <time.h>
#include <tchar.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>

#include "CInput.h"
#include "CText.h"
#include "CTexture.h"
#include "CSprite.h"
#include "CPayload.h"
#include "CPayloadManager.h"
#include "CGameObject.h"
#include "CBackground.h"

#include "GameFramework.h"

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

GameFramework::GameFramework()
{
	m_pD3D = NULL;
	m_pD3DDevice = NULL;

	// D3DCOLOR g_ClearColor = D3DCOLOR_XRGB(0, 0, 255);
	m_PCPos = D3DXVECTOR3(320, 400, 0);
	m_AlienPos = D3DXVECTOR3(100, 100, 0);

	// 스프라이트 객체 인터페이스 정의
	// m_Sprite[2]; // 0: pc, 1~19: Ailen
	m_Pause = false;
	m_dwPrevTime = 0;
	m_AlienShootTimer = 0;

	// 배경
	m_BGmoon = NULL;
	m_BGsky = NULL;
	m_BGmountain = NULL;
	m_BGground = NULL;

	m_Jump = false;
}

GameFramework::~GameFramework()
{
}

bool GameFramework::InitFramework(HWND hWnd, HINSTANCE hInstance)
{
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (m_pD3D == NULL) return false;

	RECT rc;
	GetClientRect(hWnd, &rc);

	int ClientWidth = rc.right - rc.left + 1;
	int ClientHeight = rc.bottom - rc.top + 1;
	m_ScreenWidth = 1920;
	m_ScreenHeight = 1080;

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.Windowed = TRUE;
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferWidth = 1920;
	d3dpp.BackBufferHeight = 1080;

	if (m_pD3D->CreateDevice(D3DADAPTER_DEFAULT
		, D3DDEVTYPE_HAL
		, hWnd
		, D3DCREATE_HARDWARE_VERTEXPROCESSING
		, &d3dpp
		, &m_pD3DDevice) == E_FAIL) return false;
	
	srand((unsigned int)time(NULL));

	m_Input = new CInput(hWnd, hInstance);
	m_Text = new CText(m_pD3DDevice, 20, 40);
	m_Texture = new CTexture(m_pD3DDevice);
	
	// alien motion
	m_AlienDir = D3DXVECTOR3(1, 0, 0);

	// PlaySound(_T("..//Alarm10.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

	return true;
}

void GameFramework::ReleaseFramework()
{
	delete m_Input;
	delete m_Text;
	delete m_Texture;

	if (m_pD3DDevice != NULL)
		m_pD3DDevice->Release();

	if (m_pD3D != NULL)
		m_pD3D->Release();

	m_pD3DDevice = NULL;
	m_pD3D = NULL;
}

void GameFramework::LoadTextures()
{
	m_Texture->LoadTexture(-1, TEXT("../img/pc.png"));
	m_Texture->LoadTexture(-1, TEXT("../img/ufo.png"));
	m_Texture->LoadTexture(-1, TEXT("../img/fire.png"));
	m_Texture->LoadTexture(-1, TEXT("../img/lightning.png"));
	m_Texture->LoadTexture(-1, TEXT("../img/sky.png"));
	m_Texture->LoadTexture(-1, TEXT("../img/mountain.png"));
	m_Texture->LoadTexture(-1, TEXT("../img/ground.png"));
	m_Texture->LoadTexture(-1, TEXT("../img/none.png"));
	m_Texture->LoadTexture(-1, TEXT("../img/missle.png"));
	m_Texture->LoadTexture(-1, TEXT("../img/moon.png"));

	// pcPM loadtextures함수 넣기
}

void GameFramework::ReleaseTextures()
{
}

void GameFramework::InitGameData()
{
	D3DXVECTOR3 pcPos = D3DXVECTOR3(m_ScreenWidth*0.5f, 850, 0);
	const float pcSpeed = 300.f;
	const float AlienSpeed = 100.f;
	const float TrapSpeed = 300.f;

	m_Jump = false;
	m_2ndJump = false;
	m_fJumpTime = 0.f;
	m_fJumpPower = 12.f;
	
	m_dwPrevTime = GetTickCount();
	m_AlienRightDir = true;

	//player
	m_Player = new CGameObject(m_pD3DDevice
		, m_Texture->GetTexture(0)
		, D3DXVECTOR3(66, 72, 0)
		, pcPos
		, pcSpeed);
	m_Player->SetAlive(true);

	// alien
	m_Alien = new CGameObject(m_pD3DDevice
		, m_Texture->GetTexture(1)
		, D3DXVECTOR3(64, 64, 0)
		, m_AlienPos
		, AlienSpeed);
	m_Alien->SetAlive(true);

	//trap

	// shoot sprite
	m_PCPayloadManager = new CPayloadManager(m_pD3DDevice
		, m_Texture->GetTexture(2)
		, D3DXVECTOR3(16.f, 16.f, 0.f)
		, 400.f
		, D3DXVECTOR3(0.f, -1.f, 0.f)
		, D3DXVECTOR2(m_ScreenWidth, m_ScreenHeight));

	m_AlienPayloadManager = new CPayloadManager(m_pD3DDevice
		, m_Texture->GetTexture(3)
		, D3DXVECTOR3(16.f, 16.f, 0.f)
		, 400.f
		, D3DXVECTOR3(0.f, 1.f, 0.f)
		, D3DXVECTOR2(m_ScreenWidth, m_ScreenHeight));


	// Background
	m_BGmoon = new CBackground(m_pD3DDevice,
		m_Texture->GetTexture(8)
		, D3DXVECTOR3(0, 0, 0)
		, 1920
		, 5);

	m_BGsky = new CBackground(m_pD3DDevice
		, m_Texture->GetTexture(4)
		, D3DXVECTOR3(0, 0, 0)
		, 1920
		, 15);

	m_BGmountain = new CBackground(m_pD3DDevice
		, m_Texture->GetTexture(5)
		, D3DXVECTOR3(0, 0, 0)
		, 1920
		, 50);

	m_BGground = new CBackground(m_pD3DDevice
		, m_Texture->GetTexture(6)
		, D3DXVECTOR3(0, 0, 0)
		, 1920
		, 300);

}

void GameFramework::ReleaseGameData()
{
	delete m_BGground;
	delete m_BGmountain;
	delete m_BGsky;
	delete m_BGmoon;
	delete m_PCPayloadManager;
	delete m_AlienPayloadManager;

	m_PCPayloadManager = NULL;
	m_AlienPayloadManager = NULL;

	delete m_Player;
	m_Player = NULL;

	delete m_Alien;
	m_Alien = NULL;
}

void GameFramework::GameUpdate(UINT& escapecode)
{
	if (m_Input->IsEscapePressed())
	{
		escapecode = WM_QUIT;
		return;
	}
	else
	{
		m_Input->ReadKeyboard(); // 키보드 버퍼 읽어오기

		if (m_Input->IsPausePressed()) // pause 체크
			m_Pause = !m_Pause;

		DWORD dwCurTime = GetTickCount(); // 프레임 시간 계산 부분
		DWORD dwDt = dwCurTime - m_dwPrevTime;
		float fDt = (float)(dwDt)*0.001f;
		m_dwPrevTime = dwCurTime;

		if (m_Pause == false)
		{ // start
			if (m_Pause == false && m_Input->IsSpasePressed()) //3단
				m_PCPayloadManager->OnFire3( m_Player->GetPosition());
				// m_PCPayloadManager->OnHoming(m_Player->GetPosition(), m_Alien->GetPosition());
			
			Update(fDt);
		}
	}
}

void GameFramework::GameRender()
{
	Render();
}

void GameFramework::Update(float dt)
{
	D3DXVECTOR3 pcDir(0.f, 0.f, 0.f);
	m_Input->GetArrowDir(pcDir);

	m_Player->SetDirection(pcDir.x, pcDir.y);
	m_Player->Update(dt);

	m_PCPos = m_Player->GetPosition();//??
	// 화면 이동 제한
	m_Player->ArrangePosition(175.f, m_ScreenWidth - 175.f);

	// alien 이동
	m_Alien->SetDirection(m_AlienDir.x, m_AlienDir.y);
	m_Alien->Update(dt);

	if (m_Alien->IsTouched(64.f, m_ScreenWidth - 64.f, m_AlienRightDir) == true)
	{
		m_AlienDir = D3DXVECTOR3((m_AlienRightDir) ? -1.f : 1.f, 0.f, 0.f);
		m_AlienRightDir = !m_AlienRightDir;
	}

	ProjectileUpdate(dt); // 총알 날리기
	PlayerCollisionUpadte(dt); // 사용자 맞음?
	AlienCollisionUpdate(dt); // 외계인 맞음??
	JumpUpdate(dt); // jump
	BGUpdate(dt); // 배경화면
}

void GameFramework::Render()
{
	if (m_pD3DDevice == NULL)
		return;

	// 백버퍼 지우기
	m_pD3DDevice->Clear(0, NULL
		, D3DCLEAR_TARGET
		, m_clearColor
		, 1.0f, 0);

	DrawRenderObject();
	
	// 백버퍼 전송
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void GameFramework::DrawRenderObject()
{
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{
		// background
		BGRender();

		m_Player->Render();
		m_Alien->Render();
		
		// 총알
		m_PCPayloadManager->Draw();
		m_AlienPayloadManager->Draw();

		// pcPM draw넣기
		
		m_pD3DDevice->EndScene();
	}
}

void GameFramework::ProjectileUpdate(float dt)
{
	// pc총알 발사
	m_PCPayloadManager->Update(dt);
	m_AlienPayloadManager->Update(dt);
	// m_PCPayloadManager->HomingUpdate(dt, m_Alien->GetPosition());

	int delta_time = GetTickCount() - m_AlienShootTimer;
	
	if (delta_time > 1000)
	{
		m_AlienShootTimer = GetTickCount();

		if (m_Alien->GetAlive())
		{
			m_AlienPayloadManager->OnFire(m_Alien->GetPosition());
		}
	}
}

// 외계인이 맞았는가??
void GameFramework::AlienCollisionUpdate(float dt)
{
	if ((m_Alien->GetAlive() == true) &&
		m_PCPayloadManager->IsCollision(m_Alien->GetPosition(), (64.f + 16.f)))
	{
		m_Alien->SetPosition(D3DXVECTOR3(64.f, 64.f, 0));
	}
}

void GameFramework::PlayerCollisionUpadte(float dt)
{
	if ((m_Player->GetAlive() == true) &&
		m_AlienPayloadManager->IsCollision(m_Player->GetPosition(), (72.5f + 16.f)))
	{

	}
}

void GameFramework::BGRender()
{
	m_BGsky->Render();
	m_BGmoon->Render();
	m_BGmountain->Render();
	m_BGground->Render();
}

void GameFramework::BGUpdate(float dt)
{
	m_BGsky->Update(dt);
	m_BGmoon->Update(dt);
	m_BGmountain->Update(dt);
	m_BGground->Update(dt);
}

void GameFramework::JumpUpdate(float dt)
{
	D3DXVECTOR3 pcpos = m_Player->GetPosition();

	if (m_Input->IsKeyPressed(DIK_UPARROW))
	{
		if (m_Jump == false)
		{
			m_Jump = true;
			m_2ndJump = false;
			m_fJumpTime = 0.f;
			m_fJumpPower = 12.f;
			m_fBaseHeight = pcpos.y;
			m_PrevHeight = pcpos.y;
		}
		else if (m_Falling == true && m_2ndJump == false)
		{
			m_fJumpPower = 8.f;
			m_fJumpTime = 0.f;
			m_2ndJump = true;
		}
	}

	if (m_Jump == true)
	{
		m_fJumpTime += (dt * 4.f);
		float height = m_fJumpPower + (-4.9f*(m_fJumpTime * m_fJumpTime));

		pcpos.y -= height;
		m_Falling = (pcpos.y - m_PrevHeight < 0.f) ? false : true;
		// 점프 뒤 최고점에서 떨어지는 것 체크

		if (pcpos.y > m_fBaseHeight)
		{
			pcpos.y = m_fBaseHeight;
			m_Jump = false;
		}
		m_PrevHeight = pcpos.y;
		// 계산 후 높이값. 다음 계산 시 상승/하강 체크 하기 위함
		m_Player->SetPosition(pcpos);
	}
}