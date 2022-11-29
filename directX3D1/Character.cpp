#include "Character.h"
#include "shadow.h"
#include "input.h"
#include "camera.h"
#include "bullet.h"

//マクロ定義
#define MOVE_SPEED (5.0f)

#define SPEED_DOWN (0.9f)

//グローバル変数

LPD3DXMESH g_pMeshCharacter = NULL; //メッシュ(頂点情報)へのポインタ
LPD3DXBUFFER g_pBuffMatCharacter = NULL; //マテリアルへのポインタ
DWORD g_dwNumMatCharacter = 0; //マテリアルの数
D3DXVECTOR3 g_posCharacter; //位置
D3DXVECTOR3 g_rotCharacter; //向き
D3DXMATRIX g_mtxWorldCharacter; //ワールドマトリクス
LPDIRECT3DTEXTURE9 g_pTextureCharacter[8] = {};


characte g_chara;

void InitCharacter()
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ
	pDevice = GetDevice();

	g_chara.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_chara.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_chara.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_chara.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_chara.InputCount = 0;

	g_chara.nIndexShadow = SetShadow();

	//xファイルの読み込み
	D3DXLoadMeshFromX("Data\\MODEL\\13_head.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatCharacter,
		NULL,
		&g_dwNumMatCharacter,
		&g_pMeshCharacter);

	//テクスチャの読み込み
	D3DXMATERIAL *pMat; //マテリアルデータへのポインタ
	pMat = (D3DXMATERIAL*)g_pBuffMatCharacter->GetBufferPointer();
	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatCharacter; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{//テクスチャファイルが存在する時
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_pTextureCharacter[nCntMat]);
		}
	}
}
void UninitCharacter()
{
	for (int nCntTex = 0; nCntTex < 8; nCntTex++)
	{
		if (g_pTextureCharacter[nCntTex] != NULL)
		{
			g_pTextureCharacter[nCntTex]->Release();
			g_pTextureCharacter[nCntTex] = NULL;
		}
	}
	//メッシュの破棄
	if (g_pMeshCharacter != NULL)
	{
		g_pMeshCharacter->Release();
		g_pMeshCharacter = NULL;
	}

	//マテリアルの破棄
	if (g_pBuffMatCharacter != NULL)
	{
		g_pBuffMatCharacter->Release();
		g_pBuffMatCharacter = NULL;
	}
}
void UpdateCharacter()
{
	Camera camera = GetCamera();


	//移動
	if (GetKeyboardPress(DIK_UP) == true)
	{
		g_chara.move.x += sinf(camera.rot.y)*MOVE_SPEED;
		g_chara.move.z += cosf(camera.rot.y)*MOVE_SPEED;
	}
	if (GetKeyboardPress(DIK_DOWN) == true)
	{
		g_chara.move.x -= sinf(camera.rot.y)*MOVE_SPEED;
		g_chara.move.z -= cosf(camera.rot.y)*MOVE_SPEED;
	}
	if (GetKeyboardPress(DIK_LEFT) == true)
	{
		g_chara.move.z -= sinf(-camera.rot.y)*MOVE_SPEED;
		g_chara.move.x -= cosf(-camera.rot.y)*MOVE_SPEED;
	}
	if (GetKeyboardPress(DIK_RIGHT) == true)
	{
		g_chara.move.z += sinf(-camera.rot.y)*MOVE_SPEED;
		g_chara.move.x += cosf(-camera.rot.y)*MOVE_SPEED;
	}
	if (GetKeyboardTrigger(DIK_SPACE) == true)
	{
		SetBullet(D3DXVECTOR3(g_chara.pos.x, 30.0f, g_chara.pos.z), D3DXVECTOR3(0.0f,0.0f,10.0f),g_chara.rot,20,60);
	}
	

	if (g_chara.move != D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	{
		g_chara.rotDest.y = (fmodf(((float)atan2f(g_chara.move.x, g_chara.move.z) / D3DX_PI) + 1, 2) - 1.0f) * D3DX_PI;
		g_chara.InputCount = 0;
	}
	else
	{
		g_chara.InputCount++;
	}
	
	if (g_chara.rot != g_chara.rotDest)
	{
		g_chara.rot += (g_chara.rotDest - g_chara.rot) / 10;
	}

	if (g_chara.InputCount >= 120)
	{
		TurnCamera(g_chara.rot.y);
		g_chara.InputCount = 0;
	}

	g_chara.pos += g_chara.move;
	g_chara.move.x += (0.0f - g_chara.move.x)*SPEED_DOWN;
	g_chara.move.y += (0.0f - g_chara.move.y)*SPEED_DOWN;
	g_chara.move.z += (0.0f - g_chara.move.z)*SPEED_DOWN;
	
	//影の位置
	SetPositionShadow(g_chara.nIndexShadow, g_chara.pos);
}
void DrawCharacter()
{
	
	LPDIRECT3DDEVICE9 pDevice = GetDevice(); //デバイスのポインタ
	D3DXMATRIX mtxRot, mtxTrans; //計算用マトリクス
	D3DMATERIAL9 matDef; //現在のマテリアル保存用
	D3DXMATERIAL *pMat; //マテリアルデータへのポインタ

						//ワールドマトリクスの初期化
	D3DXMatrixIdentity(&g_chara.mtx);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_chara.rot.y, g_chara.rot.x, g_chara.rot.z);
	D3DXMatrixMultiply(&g_chara.mtx, &g_chara.mtx, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_chara.pos.x, g_chara.pos.y, g_chara.pos.z);
	D3DXMatrixMultiply(&g_chara.mtx, &g_chara.mtx, &mtxTrans);

	//ワールドマトリクスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_chara.mtx);

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	//マテリアルデータのポインタを取得
	pMat = (D3DXMATERIAL*)g_pBuffMatCharacter->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatCharacter; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureCharacter[nCntMat]);

		//モデル(パーツ)の描写
		g_pMeshCharacter->DrawSubset(nCntMat);
	}
	//保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

characte Getcharacte()
{
	return g_chara;
}