#include "camera.h"
#include "input.h"
#include "character.h"

#define MOVE_SPEEDCAMERA (5.0f)
//グローバル変数
Camera g_camera;
float g_fLengthCamera;
bool g_chase;

//初期化処理
void InitCamera()
{
	g_camera.posV = D3DXVECTOR3(0.0f, 300.0f, -500.0f);
	g_camera.posR = D3DXVECTOR3(0.0f, 100.0f, 0.0f);
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_chase = true;

	g_fLengthCamera = -400.0f;

}

void UninitCamera()
{

}
void UpdateCamera()
{
	characte*pChara = &Getcharacte();

	if(GetMousePress(MOUSE_LEFT) == true)
	{

		g_camera.rot.y += GetMouseMove().x * 0.01f;
		g_camera.rot.z += GetMouseMove().y * 0.01f;
		g_camera.posV.x = g_camera.posR.x + cosf(g_camera.rot.z) * sinf(g_camera.rot.y) * g_fLengthCamera;
		g_camera.posV.z = g_camera.posR.z + cosf(g_camera.rot.z) * cosf(g_camera.rot.y) *g_fLengthCamera;
		g_camera.posV.y = g_camera.posR.y + sinf(g_camera.rot.z) *g_fLengthCamera;

	}
	if (GetMousePress(MOUSE_RIGTH) == true)
	{

		g_camera.rot.y -= GetMouseMove().x * 0.003f;
		g_camera.rot.z -= GetMouseMove().y * 0.003f;
		g_camera.posR.x = g_camera.posV.x - cosf(g_camera.rot.z) * sinf(g_camera.rot.y) * g_fLengthCamera;
		g_camera.posR.z = g_camera.posV.z - cosf(g_camera.rot.z) * cosf(g_camera.rot.y) *g_fLengthCamera;
		g_camera.posR.y = g_camera.posV.y - sinf(g_camera.rot.z) *g_fLengthCamera;

	}
	if (GetMousePress(MOUSE_CENTER) == true)
	{

		g_camera.posR.x -= GetMouseMove().x * 0.5f;
		g_camera.posR.z -= GetMouseMove().y * 0.5f;
												
		g_camera.posV.x -= GetMouseMove().x * 0.5f;
		g_camera.posV.z -= GetMouseMove().y * 0.5f;
	}
	
	if (g_chase == true)
	{
		g_camera.posRdest = pChara->pos;
		g_camera.posRdest.x = pChara->pos.x - sinf(pChara->rot.y)*(-50 - pChara->move.x);
		g_camera.posRdest.z = pChara->pos.z - cosf(pChara->rot.y)*(-50 - pChara->move.z);

		g_camera.posVdest.z = g_camera.posRdest.z + cosf(g_camera.rot.y)*(g_fLengthCamera);
		g_camera.posVdest.x = g_camera.posRdest.x + sinf(g_camera.rot.y)*(g_fLengthCamera);

		g_camera.moveV.x = -(g_camera.posV.x - g_camera.posVdest.x) / 10;
		g_camera.moveV.z = -(g_camera.posV.z - g_camera.posVdest.z) / 10;

		if (g_camera.posRdest != g_camera.posR)
		{
			if (g_camera.posR.x != g_camera.posRdest.x)
			{
				g_camera.moveR.x = -(g_camera.posR.x - g_camera.posRdest.x) / 20;
			}

			if (g_camera.posR.y != g_camera.posRdest.y)
			{
				g_camera.moveR.y = -(g_camera.posR.y - g_camera.posRdest.y) / 20;
			}

			if (g_camera.posR.z != g_camera.posRdest.z)
			{
				g_camera.moveR.z = -(g_camera.posR.z - g_camera.posRdest.z) / 20;
			}

		}

		if (g_camera.rot != g_camera.rotDest)
		{
			g_camera.rot += (g_camera.rotDest - g_camera.rot) / 50;
		}
		//位置を更新
		g_camera.posR += g_camera.moveR;
		g_camera.posV += g_camera.moveV;
	}
	/*if (GetKeyboardPress(DIK_W) == true)
	{
		g_camera.posV.x += sinf(g_camera.rot.y)*MOVE_SPEEDCAMERA;
		g_camera.posV.z += cosf(g_camera.rot.y)*MOVE_SPEEDCAMERA;

		g_camera.posR.x += sinf(g_camera.rot.y)*MOVE_SPEEDCAMERA;
		g_camera.posR.z += cosf(g_camera.rot.y)*MOVE_SPEEDCAMERA;
	}
	if (GetKeyboardPress(DIK_S) == true)
	{
		g_camera.posV.x -= sinf(g_camera.rot.y)*MOVE_SPEEDCAMERA;
		g_camera.posV.z -= cosf(g_camera.rot.y)*MOVE_SPEEDCAMERA;

		g_camera.posR.x -= sinf(g_camera.rot.y)*MOVE_SPEEDCAMERA;
		g_camera.posR.z -= cosf(g_camera.rot.y)*MOVE_SPEEDCAMERA;
	}
	if (GetKeyboardPress(DIK_A) == true)
	{
		g_camera.posV.z -= sinf(-g_camera.rot.y)*MOVE_SPEEDCAMERA;
		g_camera.posV.x -= cosf(-g_camera.rot.y)*MOVE_SPEEDCAMERA;
								
		g_camera.posR.z -= sinf(-g_camera.rot.y)*MOVE_SPEEDCAMERA;
		g_camera.posR.x -= cosf(-g_camera.rot.y)*MOVE_SPEEDCAMERA;
	}
	if (GetKeyboardPress(DIK_D) == true)
	{
		g_camera.posV.z += sinf(-g_camera.rot.y)*MOVE_SPEEDCAMERA;
		g_camera.posV.x += cosf(-g_camera.rot.y)*MOVE_SPEEDCAMERA;
								
		g_camera.posR.z += sinf(-g_camera.rot.y)*MOVE_SPEEDCAMERA;
		g_camera.posR.x += cosf(-g_camera.rot.y)*MOVE_SPEEDCAMERA;
	}*/
	

	if (GetKeyboardPress(DIK_L) == true)
	{
		g_camera.rot.y -= 0.03f;
		g_camera.posV.x = g_camera.posR.x + cosf(g_camera.rot.z) * sinf(g_camera.rot.y) * g_fLengthCamera;
		g_camera.posV.z = g_camera.posR.z + cosf(g_camera.rot.z) * cosf(g_camera.rot.y) *g_fLengthCamera;
		g_camera.posV.y = g_camera.posR.y + sinf(g_camera.rot.z) *g_fLengthCamera;
	}
	if (GetKeyboardPress(DIK_K) == true)
	{
		g_camera.rot.y += 0.03f;
		g_camera.posV.x = g_camera.posR.x + sinf(g_camera.rot.y)*g_fLengthCamera;
		g_camera.posV.z = g_camera.posR.z + cosf(g_camera.rot.y)*g_fLengthCamera;
	}
	if (GetKeyboardPress(DIK_P) == true)
	{
		g_camera.rot.y += 0.03f;
		g_camera.posR.x = g_camera.posV.x - sinf(g_camera.rot.y)*g_fLengthCamera;
		g_camera.posR.z = g_camera.posV.z - cosf(g_camera.rot.y)*g_fLengthCamera;
	}
	if (GetKeyboardPress(DIK_O) == true)
	{
		g_camera.rot.y -= 0.03f;
		g_camera.posR.x = g_camera.posV.x - sinf(g_camera.rot.y)*g_fLengthCamera;
		g_camera.posR.z = g_camera.posV.z - cosf(g_camera.rot.y)*g_fLengthCamera;
	}
	if (GetKeyboardTrigger(DIK_C) == true)
	{
		if (g_chase == false)
		{
			g_chase = true;
		}
		else
		{
			g_chase = false;
		}
	}

	

	if (g_camera.rot.y > 3.14f)
	{
		g_camera.rot.y = -3.14f;
	}
	if (g_camera.rot.y < -3.14f)
	{
		g_camera.rot.y = 3.14f;
	}
	if (g_camera.rot.z > 3.14f /2)
	{				 
		g_camera.rot.z = 3.14f / 2;
	
	}				 
	if (g_camera.rot.z < -3.14f / 2)
	{				 
		g_camera.rot.z = -3.14f / 2;
		
	}
	

	



	/*g_camera.posV.x = g_camera.posR.x + cosf(g_camera.rot.y + 1.5f)*g_fLengthCamera;
	g_camera.posV.z = g_camera.posR.y + sinf(g_camera.rot.y + 1.5f)*g_fLengthCamera;
	g_camera.posV.z = g_camera.posR.z + sinf(g_camera.rot.y + 1.5f)*g_fLengthCamera;*/

	/*if (GetKeyboardPress(DIK_UP) == true)
	{
		g_camera.posR.y += MOVE_SPEEDCAMERA;
	}
	if (GetKeyboardPress(DIK_DOWN) == true)
	{
		g_camera.posR.y -= MOVE_SPEEDCAMERA;
	}
	if (GetKeyboardPress(DIK_LEFT) == true)
	{
		g_camera.posR.x -= MOVE_SPEEDCAMERA;
	}
	if (GetKeyboardPress(DIK_RIGHT) == true)
	{
		g_camera.posR.x += MOVE_SPEEDCAMERA;
	}*/
}
void SetCamera()
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ
	pDevice = GetDevice();

	//プロジェクションマトリクスの初期化
	D3DXMatrixIdentity(&g_camera.mtxProjection);

	//プロジェクションマトリクスを作成
	D3DXMatrixPerspectiveFovLH(&g_camera.mtxProjection,
								D3DXToRadian(45.0f),
								(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
								10.0f,
								10000.0f);

	//プロジェクションマトリクスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxProjection);

	//ビューマトリクスの初期化
	D3DXMatrixIdentity(&g_camera.mtxView);

	//ビューマトリクスを作成
	D3DXMatrixLookAtLH(&g_camera.mtxView,
		&g_camera.posV,
		&g_camera.posR,
		&g_camera.vecU);

	//ビューマトリクスの設定
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);
}

void TurnCamera(float rot)
{
	g_camera.rotDest.y = rot;
	g_camera.rotDest.z = 1.0f;
}

Camera GetCamera()
{
	return g_camera;
}