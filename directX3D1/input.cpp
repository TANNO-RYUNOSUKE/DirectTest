#include "input.h"
#include <stdio.h>

//�}�N����`
#define NUM_KEY_MAX (256) //�L�[�̍ő吔
#define PLAYER_MAX (4) //�v���C���[�̍ő吔

//�O���[�o���ϐ�

//�L�[�{�[�h�p

LPDIRECTINPUT8 g_pInput = NULL;
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;
BYTE g_aKeyState[NUM_KEY_MAX]; 
BYTE g_aKeyStateTrigger[NUM_KEY_MAX];
BYTE g_aKeyStateRelease[NUM_KEY_MAX];
BYTE g_aKeyStateRepeat[NUM_KEY_MAX];
LPDIRECTINPUTDEVICE8 g_pDevMouse = NULL;
DIMOUSESTATE MouseState;


//�Q�[���p�b�h�p
XINPUT_STATE g_JoykeyState[PLAYER_MAX];
XINPUT_STATE g_JoykeyStateTrigger[PLAYER_MAX];

//�v���g�^�C�v�錾

//�L�[�{�[�h�p
HRESULT InitKeyboard( HWND hWnd);
void UninitKeyboard(void);
void UpdateKeyboard(void);

//�Q�[���p�b�h�p
HRESULT InitGamepad(void);
void UninitGamepad(void);
void UpdateGamepad(void);

//==============================
//����������
//==============================


HRESULT InitInput(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInput�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}
	if (FAILED(InitMouse(hWnd)))
	{
		return E_FAIL;
	}
	if (FAILED(InitKeyboard(hWnd)))
	{
		return E_FAIL;
	}
	if (FAILED(InitGamepad()))
	{
		return E_FAIL;
	}
	return S_OK;
}
//======================================
//�I������
//======================================
void UninitInput(void)
{
	UninitKeyboard();//�L�[�{�[�h�̏I������
	UninitGamepad();//�Q�[���p�b�h�̏I������
	UninitMouse();
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}
//======================================
//�X�V����
//======================================
void UpdateInput(void)
{
	UpdateKeyboard();//�L�[�{�[�h�̍X�V����
	UpdateGamepad();//�Q�[���p�b�h�̍X�V����
	UpdateMouse();
}
//======================================
//�v���X���
//======================================
bool GetKeyboardPress(int nKey)
{
	return (g_aKeyState[nKey] & 0X80) ? true : false;
 }
//======================================
//�g���K�[���
//======================================
bool GetKeyboardTrigger(int nKey)
{
	return (g_aKeyStateTrigger[nKey] & 0X80) ? true : false;
}
//======================================
//�����[�X���
//======================================
bool GetKeyboardRelease(int nKey)
{
	return (g_aKeyStateRelease[nKey] & 0X80) ? true : false;
}
//======================================
//���s�[�g���
//======================================
bool GetKeyboardRepeat(int nKey)
{
	return (g_aKeyStateRepeat[nKey] & 0X80) ? true : false;
}
//======================================
//�L�[�{�[�h������
//======================================
HRESULT InitKeyboard(HWND hWnd)
{
	
	//���̓f�o�C�X�̐����i�L�[�{�[�h�j
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{
		return E_FAIL;
	}
	//�f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	//�������[�h��ݒ�
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}
	//�L�[�{�[�h�̃A�N�Z�X�����擾
	g_pDevKeyboard->Acquire();

	return S_OK;
}
//======================================
//�L�[�{�[�h�I��
//======================================
void UninitKeyboard(void)
{
	//���̓f�o�C�X�̔j��
	if (g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire(); //�L�[�{�[�h�ւ̃A�N�Z�X����j��
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}

	//Directinput�I�u�W�F�N�g�̔j��
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}
//======================================
//�L�[�{�[�h�X�V
//======================================
void UpdateKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];
	int nCntKey;

	//���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			g_aKeyStateTrigger[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey])&aKeyState[nCntKey];
			g_aKeyStateRelease[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey])&g_aKeyState[nCntKey];
			g_aKeyState[nCntKey] = aKeyState[nCntKey]; //�L�[�{�[�h��PRESS����ۑ�
		}
	}
	else
	{
		g_pDevKeyboard->Acquire();
	}
}
//======================================
//�}�E�X������
//======================================
HRESULT InitMouse(HWND hWnd)
{
	//���̓f�o�C�X�̐����i�L�[�{�[�h�j
	if (FAILED(g_pInput->CreateDevice(GUID_SysMouse, &g_pDevMouse, NULL)))
	{
		return E_FAIL;
	}
	//�f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(g_pDevMouse->SetDataFormat(&c_dfDIMouse)))
	{
		return E_FAIL;
	}
	//�������[�h��ݒ�
	if (FAILED(g_pDevMouse->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	DIPROPDWORD diprop;
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = DIPROPAXISMODE_REL;

	if (FAILED(g_pDevMouse->SetProperty(DIPROP_AXISMODE,&diprop.diph)))
	{
		return E_FAIL;
	}

	//�}�E�X�̃A�N�Z�X�����擾
	g_pDevMouse->Acquire();

	return S_OK;
}
//======================================
//�}�E�X�I��
//======================================
void UninitMouse()
{
	//���̓f�o�C�X�̔j��
	if (g_pDevMouse != NULL)
	{
		g_pDevMouse->Unacquire(); //�L�[�{�[�h�ւ̃A�N�Z�X����j��
		g_pDevMouse->Release();
		g_pDevMouse = NULL;
	}

	//Directinput�I�u�W�F�N�g�̔j��
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}
//======================================
//�}�E�X�X�V
//======================================
void UpdateMouse()
{
	DIMOUSESTATE mouse;
	int nCntKey;

	//���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(g_pDevMouse->GetDeviceState(sizeof(mouse), &mouse)))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			//���͏��̕ۑ�
			MouseState = mouse;
		}
	}
	else
	{
		g_pDevMouse->Acquire();
	}
}
//======================================
//�Q�[���p�b�h������
//======================================
HRESULT InitGamepad(void)
{
	//Xinput�̃X�e�[�g�̐ݒ�
	XInputEnable(true);

	//�[���N���A
	ZeroMemory(&g_JoykeyState, sizeof(g_JoykeyState));
	ZeroMemory(&g_JoykeyStateTrigger, sizeof(g_JoykeyStateTrigger));

	return S_OK;
}
//======================================
//�Q�[���p�b�h�I��
//======================================
void UninitGamepad(void)
{
	//Xinput�̃X�e�[�g�̐ݒ�
	XInputEnable(false);
}
//======================================
//�Q�[���p�b�h�X�V
//======================================
void UpdateGamepad(void)
{
	int nCount;
	XINPUT_STATE JoykeyState;

	for ( nCount = 0; nCount < PLAYER_MAX; nCount++)
	{
		if (XInputGetState(nCount,&JoykeyState) == ERROR_SUCCESS)
		{
			g_JoykeyStateTrigger[nCount].Gamepad.wButtons = (g_JoykeyState[nCount].Gamepad.wButtons ^ JoykeyState.Gamepad.wButtons) & JoykeyState.Gamepad.wButtons;
		    g_JoykeyStateTrigger[nCount].Gamepad.bLeftTrigger = (g_JoykeyState[nCount].Gamepad.bLeftTrigger ^ JoykeyState.Gamepad.bLeftTrigger) & JoykeyState.Gamepad.bLeftTrigger;
			g_JoykeyStateTrigger[nCount].Gamepad.bRightTrigger = (g_JoykeyState[nCount].Gamepad.bRightTrigger ^ JoykeyState.Gamepad.bRightTrigger) & JoykeyState.Gamepad.bRightTrigger;

			g_JoykeyState[nCount] = JoykeyState;
		}
	}
	
}

bool GetGamepadPress(JOYKEY Key,int nPlayer)
{
	return (g_JoykeyState[nPlayer].Gamepad.wButtons & (0x01 << Key)) ? true : false;
}
bool GetGamepadTrigger(JOYKEY Key, int nPlayer)
{
	return (g_JoykeyStateTrigger[nPlayer].Gamepad.wButtons & (0x01 << Key)) ? true : false;
}

bool GetGamepadPedalTriggerL(int nPlayer)
{
	return (g_JoykeyStateTrigger[nPlayer].Gamepad.bLeftTrigger & (0x01 << '\0' )) ? true : false;
}
bool GetGamepadPedalTriggerR(int nPlayer)
{
	return (g_JoykeyStateTrigger[nPlayer].Gamepad.bRightTrigger & (0x01 << '\0')) ? true : false;
}

D3DXVECTOR3 GetGamePadStickL(int nPlayer, float Dead)
{
	D3DXVECTOR3 Stick = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	Stick.x = (float)g_JoykeyState[nPlayer].Gamepad.sThumbLX / SHRT_MAX;
	if (fabsf(Stick.x) < Dead)
	{
		Stick.x = 0.0f;
	}

	Stick.y = (float)g_JoykeyState[nPlayer].Gamepad.sThumbLY / SHRT_MAX;
	if (fabsf(Stick.y) < Dead)
	{
		Stick.y = 0.0f;
	}
	Stick.y *= -1;

	return Stick;
}
D3DXVECTOR3 GetGamePadStickR(int nPlayer, float Dead)
{
	D3DXVECTOR3 Stick = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	Stick.x = (float)g_JoykeyState[nPlayer].Gamepad.sThumbRX / (SHRT_MAX);
	if (fabsf(Stick.x) < Dead)
	{
		Stick.x = 0.0f;
	}

	Stick.y = (float)g_JoykeyState[nPlayer].Gamepad.sThumbRY / (SHRT_MAX);
	if (fabsf(Stick.y) < Dead)
	{
		Stick.y = 0.0f;
	}
	Stick.y *= -1;

	return Stick;
}

//=============================
//�}�E�X�̃f�o�b�O
//=============================
void GetMouseDebug(void)
{
	//���[�J���ϐ��錾
	char aStr[256];

	//�t�H���g�̎擾
	LPD3DXFONT  pFont = GetFont();

	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		RECT rect = { 0,nCnt * 20,SCREEN_WIDTH,SCREEN_HEIGHT };

		if (nCnt < 4)
		{
			sprintf(&aStr[0], "�}�E�X�̏��:%d", MouseState.rgbButtons[nCnt]);
		}
		pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

}

//=============================
//�}�E�X�̓���
//=============================
bool GetMousePress(MOUSE nKey)
{
	return (MouseState.rgbButtons[nKey] & 0x80) ? true : false;
}

D3DXVECTOR3 GetMouseMove(void)
{
	return D3DXVECTOR3(((float)MouseState.lX) , (-(float)MouseState.lY) , (-(float)MouseState.lZ));
}