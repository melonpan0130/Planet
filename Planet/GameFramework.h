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

	void ProjectileUpdate(float dt); // pc, Alien �Ѿ� �߻�
	void AlienCollisionUpdate(float dt); // ���� �¾ҳ�?
	void PlayerCollisionUpadte(float dt); // ���� �¾ҳ�?

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

	// class ���
	CInput* m_Input;
	CText* m_Text;
	CTexture* m_Texture;
	bool m_Pause; // pause
	DWORD m_dwPrevTime;
	bool m_AlienRightDir; // alien�� ����

	// �Ѿ� �߻�
	CPayloadManager* m_PCPayloadManager;
	CPayloadManager* m_AlienPayloadManager;
	DWORD m_AlienShootTimer;

	CGameObject* m_Player;
	CGameObject* m_Alien;
	CGameObject* m_Trap[10];

	// ���
	CBackground* m_BGmoon;
	CBackground* m_BGsky;
	CBackground* m_BGmountain;
	CBackground* m_BGground;

	bool m_Jump;
	bool m_2ndJump; // �ι�° �������ΰ�
	bool m_Falling; // �������� ��
	float m_fJumpPower; // 1�� 12, 2�� 8
	float m_fBaseHeight; // 
	float m_PrevHeight; // ���� ����
	float m_fJumpTime;
};