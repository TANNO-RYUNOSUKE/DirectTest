#include "main.h"
#include "Wall.h"
#include "input.h"

//マクロ定義
#define MAX_WALL (255)

//グローバル変数

LPDIRECT3DTEXTURE9 g_pTextureWall = NULL; //テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall = NULL; //頂点バッファへのポインタ
WALL g_Wall[MAX_WALL];

void InitWall(void)
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ
	pDevice = GetDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		"Data\\TEXTURE\\water02.jpg",
		&g_pTextureWall);

	for (int nCnt = 0; nCnt < MAX_WALL; nCnt++)
	{
		g_Wall[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Wall[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Wall[nCnt].bUse = false;
	}
	
	

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_WALL,
		D3DUSAGE_WRITEONLY,
		{ FVF_VERTEX_3D },
		D3DPOOL_MANAGED,
		&g_pVtxBuffWall,
		NULL);

	VERTEX_3D * pVtx;
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCnt = 0; nCnt < MAX_WALL; nCnt++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-300.0f, +600.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(+300.0f, +600.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-300.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(+300.0f, 0.0f, 0.0f);

		//法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		pVtx += 4;
	}
	g_pVtxBuffWall->Unlock();
}




//プレイヤーの終了処理
void UninitWall(void)
{
	if (g_pTextureWall != NULL)
	{
		g_pTextureWall->Release();
		g_pTextureWall = NULL;
	}
	if (g_pVtxBuffWall != NULL)
	{
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}
}

//プレイヤーの更新処理
void UpdateWall(void)
{
	
}

//プレイヤーの描画処理
void DrawWall(void)
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ
	pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans; //計算用マトリクス

	for (int nCnt = 0; nCnt < MAX_WALL; nCnt++)
	{
		if (g_Wall[nCnt].bUse == true)
		{
			//ワールドマトリクスの初期化
			D3DXMatrixIdentity(&g_Wall[nCnt].mtx);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Wall[nCnt].rot.y, g_Wall[nCnt].rot.x, g_Wall[nCnt].rot.z);

			D3DXMatrixMultiply(&g_Wall[nCnt].mtx, &g_Wall[nCnt].mtx, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Wall[nCnt].pos.x, g_Wall[nCnt].pos.y, g_Wall[nCnt].pos.z);

			D3DXMatrixMultiply(&g_Wall[nCnt].mtx, &g_Wall[nCnt].mtx, &mtxTrans);

			//ワールドマトリクスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Wall[nCnt].mtx);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffWall, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureWall);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCnt, 2);
		}
	}
}