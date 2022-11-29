#include"main.h"
#include "input.h"
#include "Field.h"
#include "camera.h"
#include "light.h"
#include "Character.h"
#include "shadow.h"
#include "wall.h"
#include "Bullet.h"
#include "Effect.h"
#include "particle.h"
#include "explosion.h"
#include "meshfield.h"
#include "meshwall.h"
#include "meshcylinder.h"
#include "model.h"

//�}�N����`
#define CLASS_NAME "WindowClass"     //�E�B���h�E�N���X�̖��O
#define WINDOW_NAME "Labyrinth in Sanity"  //�E�B���h�E�̖��O
#define ID_TIMER (131)
#define TIMER_INTERVAL (1000/60)


//�v���g�^�C�v�錾
LRESULT CALLBACK WindowPloc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

LPDIRECT3DDEVICE9 GetDevice(void);

HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);

void DrawFPS(void);

//�O���[�o���ϐ�
LPDIRECT3D9 g_pD3D = NULL;
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;
LPD3DXFONT g_pFont = NULL;
Camera g_rotcamera = GetCamera();



int g_nCountFPS = 0;


bool g_bDispDebug = false;

MODE g_mode = MODE_TITLE;//�J�n���_�̃��[�h

//=============================================
//���C���֐�
//=============================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePlev, LPSTR lpCmdline, int nCmdShow)
{
	DWORD dwCurrentTime;
	DWORD dwExecLastTime;
	DWORD dwFrameCount;
	DWORD dwFPSLastTime;

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),//WNDCLASSEX�̃������T�C�Y
		CS_CLASSDC,//�E�B���h�E�X�^�C��
		WindowPloc, //�E�B���h�E�v���V�[�W��
		0, //�ʏ�g�p���Ȃ�
		0, //�ʏ�g�p���Ȃ�
		hInstance, //�C���X�^���X�n���h��
		LoadIcon(NULL,IDI_APPLICATION),//�}�E�X�J�[�\��
		LoadCursor(NULL,IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		LoadIcon(NULL,IDI_APPLICATION)
	};

	

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	HWND hWnd; //�E�B���h�E�n���h��
	MSG msg;

	

	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//�E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	//�E�B���h�E�𐶐�
	hWnd = CreateWindowEx(0,
		CLASS_NAME,//�E�B���h�E�N���X�̖��O
		WINDOW_NAME,//�E�B���h�E�̖��O
		WS_OVERLAPPEDWINDOW,//�E�B���h�E�X�^�C��
		CW_USEDEFAULT,//�E�B���h�E�����X���W
		CW_USEDEFAULT,//�E�B���h�E�����Y���W
		(rect.right -rect.left),//��
		(rect.bottom - rect.top),//����
		NULL,//�e�E�B���h�E�̃n���h��
		NULL,//���j���[�n���h���܂��͎q�E�B���h�E��ID
		hInstance,//�C���X�^���X�n���h��
		NULL);
	
	//�������ݒ�
	if (FAILED(Init(hInstance,hWnd,TRUE)))
	{
		return -1;
	};

	//����\��ݒ�
	timeBeginPeriod(1);
	dwCurrentTime = 0;
	dwExecLastTime = timeGetTime();//���ݎ������擾
	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();
	ShowWindow(hWnd, nCmdShow);//�E�B���h�E�̕\����Ԃ�ݒ�
	DispatchMessage(&msg);
	//���b�Z�[�W���[�v
 	while (1)
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE) != 0)
		{//Windows�̏���
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				//���b�Z�[�W�̐ݒ�
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{//DirectX�̏���
			dwCurrentTime = timeGetTime();
			
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{//0.5�b�o��
				//FPS���v��
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);

				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}
			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{//60���̂P�b�o��
				dwExecLastTime = dwCurrentTime;

				//�X�V����
				Update();
				//�`�揈��
				Draw();

				dwFrameCount++; //�t���[���J�E���g�����Z
			}
			
		}
			}
		Uninit();
		return (int)msg.wParam;

	UnregisterClass(CLASS_NAME, wcex.hInstance);
	return (int)msg.wParam;

	return 0;


}
//=============================================
//�E�B���h�E�v���V�[�W��
//=============================================
LRESULT CALLBACK WindowPloc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;
	

	switch (uMsg)
	{
	case WM_DESTROY: //�E�B���h�E��j��
		PostQuitMessage(0);
		break;
	
	case WM_KEYDOWN: //�L�[�������ꂽ��
		switch (wParam)
		{
		case VK_ESCAPE:
			nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO);
			if (nID == IDYES)
			{
				//�E�B���h�E��j��
				DestroyWindow(hWnd);
			}
			break;
		}
		break;
	case WM_CLOSE:
		nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO);
		if (nID == IDYES)
		{
			//�E�B���h�E��j��
			DestroyWindow(hWnd);
		}
		else if (nID == IDNO)
		{
			return 0;
		}
		break;
	case WM_LBUTTONDOWN: //���N���b�N
						 //�ΏۃE�B���h�E�Ƀt�H�[�J�X
		SetFocus(hWnd);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
//=============================================
//����������
//=============================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;
	D3DPRESENT_PARAMETERS d3dpp;

	//DirectX�I�u�W�F�N�g�̐���
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
		if (g_pD3D == NULL)
		{
			return E_FAIL;
		}
		if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT,&d3ddm)))
		{
			return E_FAIL;
		}
		ZeroMemory(&d3dpp, sizeof(d3dpp)); //�p�����[�^�̃[���N���A
		d3dpp.BackBufferWidth = SCREEN_WIDTH;
		d3dpp.BackBufferHeight = SCREEN_HEIGHT;
		d3dpp.BackBufferFormat = d3ddm.Format;
		d3dpp.BackBufferCount = 1;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.EnableAutoDepthStencil = true;
		d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
		d3dpp.Windowed = bWindow;
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

		//Direct3D�f�o�C�X�̐���
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_HARDWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_HAL,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))
			{
				if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
					D3DDEVTYPE_REF,
					hWnd,
					D3DCREATE_SOFTWARE_VERTEXPROCESSING,
					&d3dpp,
					&g_pD3DDevice)))
				{
					return E_FAIL;
				}
			}
		}
		//�����_�[�X�e�[�g�̐ݒ�
		g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);//�J�����O�̐ݒ�
		g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		//�T���v���[�X�e�[�g�̐ݒ�
		g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
		g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

		//�e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
		g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
		g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

		D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &g_pFont);
		//�����x�̐ݒ�
	
		
		InitInput(hInstance,hWnd);
		InitModel();
		InitMeshField();
		InitMeshWall();
		InitMeshCylinder();
		InitCamera();
		InitLight();
		InitEffect();
		InitParticle();
		InitShadow();
		InitCharacter();
		InitWall();
		InitBullet();
		InitExplosion();
		//�e��I�u�W�F�N�g�����������͂���
		return S_OK;
}
//=============================================
//�I������
//=============================================
void Uninit(void)
{
	//�e��I�u�W�F�N�g�̏I������
	UninitMeshField();
	UninitLight();
	UninitCamera();
	UninitCharacter();
	UninitMeshWall();
	UninitMeshCylinder();
	UninitModel();
	
	UninitShadow();
	UninitWall();
	UninitBullet();
	UninitEffect();
	UninitExplosion();
	UninitInput();
	//�f�o�b�O�\���j��
	if (g_pFont != NULL)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}
	//DirectX3d�f�o�C�X�̔j��
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}
	//DirectX3d�I�u�W�F�N�g�̔j��
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}
//=============================================
//�X�V����
//=============================================
void Update(void)
{
	//�e��I�u�W�F�N�g�̍X�V����
	UpdateInput();
	UpdateCamera();
	UpdateCharacter();
	UpdateWall();
	UpdateBullet();
	UpdateParticle();
	UpdateEffect();
	UpdateExplosion();
	g_rotcamera = GetCamera();

}
//=============================================
//�`�揈��
//=============================================
void Draw(void)
{
	//��ʃN���A
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//�`��J�n
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{//���������ꍇ
	
		
		SetCamera();
	
		DrawMeshField();
		DrawWall();
		DrawMeshWall();
		DrawMeshCylinder();
		DrawExplosion();
		DrawEffect();
		DrawBullet();
		DrawShadow();
		DrawCharacter();
		DrawFPS();
		
		
		g_pD3DDevice->EndScene();
	}

	//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);

}
//=============================================
//�f�o�b�O�\��
//=============================================

void DrawFPS(void)
{
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	
	char aStr[256][8];
	

		//������ɑ��
		wsprintf(&aStr[0][0], "FPS:%d", g_nCountFPS);
	    //�e�L�X�g��`��
		g_pFont->DrawText(NULL, &aStr[0][0], -1, &rect, DT_RIGHT, D3DCOLOR_RGBA(255, 255, 255, 255));

		GetMouseDebug();
}
//=============================================
//�f�o�C�X�̎擾
//=============================================

LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//void SetMode(MODE mode)
//{
//	switch (g_mode)
//	{
//	default:
//		break;
//	}
//	g_mode = mode;
//}
MODE GetMode(void)
{
	return g_mode;
}

LPD3DXFONT GetFont()
{
	return g_pFont;
}