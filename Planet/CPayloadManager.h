#pragma once

#define PAYLOAD_MAX 10
class CSprite;
class CPayload;

class CPayloadManager
{
protected:
	CPayload* m_Payload[PAYLOAD_MAX];

	int homing[5] = { -1 };

public:
	explicit CPayloadManager(LPDIRECT3DDEVICE9 pD3DDevice
		, LPDIRECT3DTEXTURE9 texture
		, const D3DXVECTOR3 & center
		, float speed, const D3DXVECTOR3 & dir
		, const D3DXVECTOR2 & screensize);
	virtual ~CPayloadManager();

	int getEmptyPayload();

	void Update(float dt);
	void Draw();

	void OnFire(const D3DXVECTOR3& pos);
	void OnFire(const D3DXVECTOR3& pos, const D3DXVECTOR3& dir);
	void OnFire3(const D3DXVECTOR3& pos);

	void OnHoming(const D3DXVECTOR3& pos, const D3DXVECTOR3& target);
	void HomingUpdate(float dt
		, const D3DXVECTOR3& target);

	bool IsCollision(const D3DXVECTOR3& pos, float radious);
};

