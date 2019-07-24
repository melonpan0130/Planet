#pragma once
#include <d3d9.h>
#include <d3dx9.h>

class CInput;
class CText;
class CTexture;
class CSprite;
class CPayload;
class CPayloadManager;
class CGameObject;
class CBackground;
class pcPM;

class GameFramework
{
public:
	GameFramework();
	virtual ~GameFramework();

	bool InitFramework(HWND hWnd, HINSTANCE hInstance);
	void ReleaseFramework();

	// textures
	void LoadTextures();
	void ReleaseTextures();

	void InitGameData();
	void ReleaseGameData();

	void GameUpdate(UINT& escapecode);
	void GameRender();

	void Update(float dt);
	void Render();

	void DrawRenderObject();

	void ProjectileUpdate(float dt); // pc, Alien 총알 발사
	void AlienCollisionUpdate(float dt); // 적이 맞았나?
	void PlayerCollisionUpadte(float dt); // 내가 맞았나?

	void BGRender();
	void BGUpdate(float dt);

	void JumpUpdate(float dt);
	
protected:
	LPDIRECT3D9 m_pD3D;
	LPDIRECT3DDEVICE9 m_pD3DDevice;
	D3DCOLOR m_clearColor;
	float m_ScreenWidth;
	float m_ScreenHeight;

	//player
	D3DXVECTOR3 m_PCPos;
	D3DXVECTOR3 m_AlienPos;
	D3DXVECTOR3 m_AlienDir;
	D3DXVECTOR3 m_TrapPos[10];

	D3DXVECTOR3 m_TrapDir;

	// class 사용
	CInput* m_Input;
	CText* m_Text;
	CTexture* m_Texture;
	bool m_Pause; // pause
	DWORD m_dwPrevTime;
	bool m_AlienRightDir; // alien의 방향

	// 총알 발사
	CPayloadManager* m_PCPayloadManager;
	CPayloadManager* m_AlienPayloadManager;
	DWORD m_AlienShootTimer;

	CGameObject* m_Player;
	CGameObject* m_Alien;
	CGameObject* m_Trap[10];

	// 배경
	CBackground* m_BGmoon;
	CBackground* m_BGsky;
	CBackground* m_BGmountain;
	CBackground* m_BGground;

	bool m_Jump;
	bool m_2ndJump; // 두번째 점프중인가
	bool m_Falling; // 떨어지는 중
	float m_fJumpPower; // 1단 12, 2단 8
	float m_fBaseHeight; // 
	float m_PrevHeight; // 이전 높이
	float m_fJumpTime;
};