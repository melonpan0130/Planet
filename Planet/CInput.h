#pragma once
#include <dinput.h>

class CInput
{
public:
	explicit CInput(HWND hWnd, HINSTANCE hInstance);
	virtual ~CInput();

	int InitInput(HWND hWnd, HINSTANCE hInstance);
	void ShutdownInput();
	bool ReadKeyboard();
	bool IsEscapePressed();
	bool IsPausePressed();
	bool IsUpPressed();
	bool IsSpasePressed();
	void GetArrowDir(D3DXVECTOR3& vecDir);

	float IsKeyPressed(int key)
	{
		return (m_keyboardState[key] & 0x80) ? 1.0f : 0.0f;
	}

	void ClearKeyBuffer()
	{
		SecureZeroMemory(m_keyboardState, sizeof(m_keyboardState));
	}

protected:
	LPDIRECTINPUT8 m_lpDInput;
	LPDIRECTINPUTDEVICE8 m_lpKeyboard;
	unsigned char m_keyboardState[256];
};