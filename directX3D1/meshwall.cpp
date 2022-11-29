#include "main.h"
#include "MeshWall.h"

//グローバル変数

LPDIRECT3DTEXTURE9 g_pTextureMeshWall = NULL; //テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshWall = NULL; //頂点バッファへのポインタ
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshWall = NULL; //インデックスバッファへのポインタ

D3DXVECTOR3 g_posMeshWall;
D3DXVECTOR3 g_rotMeshWall;
D3DXMATRIX g_mtxWorldMeshWall;
int g_nSplitBesideWall;
int g_nSplitVerticalWall;
float g_fWidthWall;

void InitMeshWall(void)
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ
	pDevice = GetDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		"Data\\TEXTURE\\water02.jpg",
		&g_pTextureMeshWall);

	g_posMeshWall = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotMeshWall = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_nSplitBesideWall = 3;
	g_nSplitVerticalWall = 5;
	g_fWidthWall = 100.0f;

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * (g_nSplitBesideWall * g_nSplitVerticalWall),
		D3DUSAGE_WRITEONLY,
		{ FVF_VERTEX_3D },
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshWall,
		NULL);

	pDevice->CreateIndexBuffer(sizeof(WORD) * ((g_nSplitVerticalWall * 2 * (g_nSplitBesideWall - 1)) + ((g_nSplitBesideWall - 2) * 2)), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_pIdxBuffMeshWall, NULL);

	VERTEX_3D * pVtx;
	g_pVtxBuffMeshWall->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	for (int nB = 0; nB < g_nSplitBesideWall; nB++)
	{
		for (int nV = 0; nV < g_nSplitVerticalWall; nV++)
		{
			pVtx[(nV + (nB * g_nSplitVerticalWall))].pos = D3DXVECTOR3((-g_fWidthWall * (g_nSplitVerticalWall - 1) / 2) + g_fWidthWall * nV, (g_fWidthWall * (g_nSplitBesideWall - 1) ) + -g_fWidthWall * nB, 0.0f);
		}
	}

	//法線ベクトルの設定
	for (int nCnt = 0; nCnt < (g_nSplitBesideWall * g_nSplitVerticalWall); nCnt++)
	{
		pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	}

	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[8].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点カラーの設定

	for (int nCnt = 0; nCnt < (g_nSplitBesideWall * g_nSplitVerticalWall); nCnt++)
	{
		pVtx[nCnt].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	}


	g_pVtxBuffMeshWall->Unlock();

	WORD*pIdx; //インデックス情報へのポインタ
			   //インデックスバッファをロックし、頂点番号データへのポインタを取得
	g_pIdxBuffMeshWall->Lock(0, 0, (void**)&pIdx, 0);
	int nCnt1;
	int nCnt2;
	int nPlus = 0;

	for (nCnt1 = 0; nCnt1 < g_nSplitBesideWall-1; nCnt1++)
	{
		for (nCnt2 = 0; nCnt2 < g_nSplitVerticalWall; nCnt2++)
		{
			pIdx[(nCnt2 * 2) + (nCnt1 * g_nSplitVerticalWall * 2) + nPlus] = nCnt2 + ((nCnt1 + 1)*g_nSplitVerticalWall);
			pIdx[(nCnt2 * 2) + (nCnt1 * g_nSplitVerticalWall * 2) + 1 + nPlus] = nCnt2 + ((nCnt1)*g_nSplitVerticalWall);
		}
		if (nCnt1 < g_nSplitBesideWall - 2)
		{
			pIdx[(nCnt2 * 2) + (nCnt1 * g_nSplitVerticalWall * 2) + nPlus] = (nCnt2 - 1) + ((nCnt1)*g_nSplitVerticalWall);
			pIdx[(nCnt2 * 2) + (nCnt1 * g_nSplitVerticalWall * 2) + 1 + nPlus] = nCnt2 + ((nCnt1 + 1)*g_nSplitVerticalWall);
			nPlus += 2;
		}

	}

	//頂点番号データの設定
	//pIdx[0] = 3;
	//pIdx[1] = 0;
	//pIdx[2] = 4;
	//pIdx[3] = 1;
	//pIdx[4] = 5;
	//pIdx[5] = 2;
	//pIdx[6] = 2;
	//pIdx[7] = 6;
	//pIdx[8] = 6;
	//pIdx[9] = 3;
	//pIdx[10] = 7;
	//pIdx[11] = 4;
	//pIdx[12] = 8;
	//pIdx[13] = 5;
	g_pIdxBuffMeshWall->Unlock();
}




//プレイヤーの終了処理
void UninitMeshWall(void)
{
	if (g_pTextureMeshWall != NULL)
	{
		g_pTextureMeshWall->Release();
		g_pTextureMeshWall = NULL;
	}
	if (g_pVtxBuffMeshWall != NULL)
	{
		g_pVtxBuffMeshWall->Release();
		g_pVtxBuffMeshWall = NULL;
	}
	if (g_pIdxBuffMeshWall != NULL)
	{
		g_pIdxBuffMeshWall->Release();
		g_pIdxBuffMeshWall = NULL;
	}
}

//プレイヤーの更新処理
void UpdateMeshWall(void)
{

}

//プレイヤーの描画処理
void DrawMeshWall(void)
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ
	pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans; //計算用マトリクス

								 //ワールドマトリクスの初期化
	D3DXMatrixIdentity(&g_mtxWorldMeshWall);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshWall.y, g_rotMeshWall.x, g_rotMeshWall.z);

	D3DXMatrixMultiply(&g_mtxWorldMeshWall, &g_mtxWorldMeshWall, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_posMeshWall.x, g_posMeshWall.y, g_posMeshWall.z);

	D3DXMatrixMultiply(&g_mtxWorldMeshWall, &g_mtxWorldMeshWall, &mtxTrans);

	//ワールドマトリクスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshWall);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffMeshWall, 0, sizeof(VERTEX_3D));

	//インデックスバッファをデータストリームに設定
	pDevice->SetIndices(g_pIdxBuffMeshWall);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureMeshWall);


	//ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, (g_nSplitBesideWall * g_nSplitVerticalWall), 0, (g_nSplitVerticalWall * 2 * (g_nSplitBesideWall - 1) + ((g_nSplitBesideWall - 3) * 2)));

}

bool CollisionWall(D3DXVECTOR3 pos, D3DXVECTOR3 Oldpos)
{
	D3DXVECTOR3 vecMove = pos - Oldpos;
	VERTEX_3D * pVtx;
	g_pVtxBuffMeshWall->Lock(0, 0, (void**)&pVtx, 0);
	D3DXVECTOR3 vecLine = pVtx[0].pos - pVtx[g_nSplitVerticalWall - 1].pos;
	D3DXVECTOR3 vecToPos = pVtx[0].pos - pos;
	g_pIdxBuffMeshWall->Unlock();
	if ((vecLine.z * vecToPos.x) - (vecLine.x * vecToPos.z) > 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}