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

//マクロ定義
#define CLASS_NAME "WindowClass"     //ウィンドウクラスの名前
#define WINDOW_NAME "Labyrinth in Sanity"  //ウィンドウの名前
#define ID_TIMER (131)
#define TIMER_INTERVAL (1000/60)


//プロトタイプ宣言
LRESULT CALLBACK WindowPloc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

LPDIRECT3DDEVICE9 GetDevice(void);

HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);

void DrawFPS(void);

//グローバル変数
LPDIRECT3D9 g_pD3D = NULL;
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;
LPD3DXFONT g_pFont = NULL;
Camera g_rotcamera = GetCamera();



int g_nCountFPS = 0;


bool g_bDispDebug = false;

MODE g_mode = MODE_TITLE;//開始時点のモード

//=============================================
//メイン関数
//=============================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePlev, LPSTR lpCmdline, int nCmdShow)
{
	DWORD dwCurrentTime;
	DWORD dwExecLastTime;
	DWORD dwFrameCount;
	DWORD dwFPSLastTime;

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),//WNDCLASSEXのメモリサイズ
		CS_CLASSDC,//ウィンドウスタイル
		WindowPloc, //ウィンドウプロシージャ
		0, //通常使用しない
		0, //通常使用しない
		hInstance, //インスタンスハンドル
		LoadIcon(NULL,IDI_APPLICATION),//マウスカーソル
		LoadCursor(NULL,IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		LoadIcon(NULL,IDI_APPLICATION)
	};

	

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	HWND hWnd; //ウィンドウハンドル
	MSG msg;

	

	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	//ウィンドウを生成
	hWnd = CreateWindowEx(0,
		CLASS_NAME,//ウィンドウクラスの名前
		WINDOW_NAME,//ウィンドウの名前
		WS_OVERLAPPEDWINDOW,//ウィンドウスタイル
		CW_USEDEFAULT,//ウィンドウ左上のX座標
		CW_USEDEFAULT,//ウィンドウ左上のY座標
		(rect.right -rect.left),//幅
		(rect.bottom - rect.top),//高さ
		NULL,//親ウィンドウのハンドル
		NULL,//メニューハンドルまたは子ウィンドウのID
		hInstance,//インスタンスハンドル
		NULL);
	
	//初期化設定
	if (FAILED(Init(hInstance,hWnd,TRUE)))
	{
		return -1;
	};

	//分解能を設定
	timeBeginPeriod(1);
	dwCurrentTime = 0;
	dwExecLastTime = timeGetTime();//現在時刻を取得
	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();
	ShowWindow(hWnd, nCmdShow);//ウィンドウの表示状態を設定
	DispatchMessage(&msg);
	//メッセージループ
 	while (1)
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE) != 0)
		{//Windowsの処理
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				//メッセージの設定
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{//DirectXの処理
			dwCurrentTime = timeGetTime();
			
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{//0.5秒経過
				//FPSを計測
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);

				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}
			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{//60分の１秒経過
				dwExecLastTime = dwCurrentTime;

				//更新処理
				Update();
				//描画処理
				Draw();

				dwFrameCount++; //フレームカウントを加算
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
//ウィンドウプロシージャ
//=============================================
LRESULT CALLBACK WindowPloc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;
	

	switch (uMsg)
	{
	case WM_DESTROY: //ウィンドウを破棄
		PostQuitMessage(0);
		break;
	
	case WM_KEYDOWN: //キーが押された時
		switch (wParam)
		{
		case VK_ESCAPE:
			nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO);
			if (nID == IDYES)
			{
				//ウィンドウを破棄
				DestroyWindow(hWnd);
			}
			break;
		}
		break;
	case WM_CLOSE:
		nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO);
		if (nID == IDYES)
		{
			//ウィンドウを破棄
			DestroyWindow(hWnd);
		}
		else if (nID == IDNO)
		{
			return 0;
		}
		break;
	case WM_LBUTTONDOWN: //左クリック
						 //対象ウィンドウにフォーカス
		SetFocus(hWnd);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
//=============================================
//初期化処理
//=============================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;
	D3DPRESENT_PARAMETERS d3dpp;

	//DirectXオブジェクトの生成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
		if (g_pD3D == NULL)
		{
			return E_FAIL;
		}
		if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT,&d3ddm)))
		{
			return E_FAIL;
		}
		ZeroMemory(&d3dpp, sizeof(d3dpp)); //パラメータのゼロクリア
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

		//Direct3Dデバイスの生成
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
		//レンダーステートの設定
		g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);//カリングの設定
		g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		//サンプラーステートの設定
		g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
		g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

		//テクスチャステージステートの設定
		g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
		g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

		D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &g_pFont);
		//透明度の設定
	
		
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
		//各種オブジェクト初期化処理はここ
		return S_OK;
}
//=============================================
//終了処理
//=============================================
void Uninit(void)
{
	//各種オブジェクトの終了処理
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
	//デバッグ表示破棄
	if (g_pFont != NULL)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}
	//DirectX3dデバイスの破棄
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}
	//DirectX3dオブジェクトの破棄
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}
//=============================================
//更新処理
//=============================================
void Update(void)
{
	//各種オブジェクトの更新処理
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
//描画処理
//=============================================
void Draw(void)
{
	//画面クリア
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//描画開始
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{//成功した場合
	
		
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

	//バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);

}
//=============================================
//デバッグ表示
//=============================================

void DrawFPS(void)
{
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	
	char aStr[256][8];
	

		//文字列に代入
		wsprintf(&aStr[0][0], "FPS:%d", g_nCountFPS);
	    //テキストを描画
		g_pFont->DrawText(NULL, &aStr[0][0], -1, &rect, DT_RIGHT, D3DCOLOR_RGBA(255, 255, 255, 255));

		GetMouseDebug();
}
//=============================================
//デバイスの取得
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