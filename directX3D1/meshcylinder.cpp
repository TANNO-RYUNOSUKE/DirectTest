#include "main.h"
#include "MeshCylinder.h"

//グローバル変数

LPDIRECT3DTEXTURE9 g_pTextureMeshCylinder = NULL; //テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshCylinder = NULL; //頂点バッファへのポインタ
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshCylinder = NULL; //インデックスバッファへのポインタ

D3DXVECTOR3 g_posMeshCylinder;
D3DXVECTOR3 g_rotMeshCylinder;
D3DXMATRIX g_mtxWorldMeshCylinder;

int g_nSplitBesideCylinder;
int g_nSplitVerticalCylinder;
float g_fWidthCylinder;
float g_fRad;

void InitMeshCylinder(void)
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ
	pDevice = GetDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		"Data\\TEXTURE\\water02.jpg",
		&g_pTextureMeshCylinder);

	g_posMeshCylinder = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotMeshCylinder = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


	g_nSplitVerticalCylinder = 9;
	g_nSplitBesideCylinder = 2;
	g_fWidthCylinder = 100.0f;
	g_fRad = 500.0f;

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * (2 * g_nSplitVerticalCylinder),
		D3DUSAGE_WRITEONLY,
		{ FVF_VERTEX_3D },
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshCylinder,
		NULL);

	pDevice->CreateIndexBuffer(sizeof(WORD) * (g_nSplitVerticalCylinder * 2 ), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_pIdxBuffMeshCylinder, NULL);

	VERTEX_3D * pVtx;
	g_pVtxBuffMeshCylinder->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	//for (int nB = 0; nB < g_nSplitBesideCylinder; nB++)
	//{
	//	for (int nV = 0; nV < g_nSplitVerticalCylinder; nV++)
	//	{
	//		pVtx[(nV + (nB * g_nSplitVerticalCylinder))].pos = D3DXVECTOR3(sinf(g_rotMeshCylinder.y + 100.0f)*g_fRad,g_fWidthCylinder * nB, cosf(g_rotMeshCylinder.y + 100.0f)*g_fRad);
	//		g_rotMeshCylinder.y += (D3DX_PI / (((float)g_nSplitVerticalCylinder-1) / 2));
	//	}
	//}
	pVtx[0].pos = D3DXVECTOR3(sinf(((D3DX_PI / 4) * 0) + 100.0f)*g_fRad, 0.0f, cosf(((D3DX_PI / 4) * 0) + 100.0f)*g_fRad);
	pVtx[1].pos = D3DXVECTOR3(sinf(((D3DX_PI / 4) * 1) + 100.0f)*g_fRad, 0.0f, cosf(((D3DX_PI / 4) * 1) + 100.0f)*g_fRad);
	pVtx[2].pos = D3DXVECTOR3(sinf(((D3DX_PI / 4) * 2) + 100.0f)*g_fRad, 0.0f, cosf(((D3DX_PI / 4) * 2) + 100.0f)*g_fRad);
	pVtx[3].pos = D3DXVECTOR3(sinf(((D3DX_PI / 4) * 3) + 100.0f)*g_fRad, 0.0f, cosf(((D3DX_PI / 4) * 3) + 100.0f)*g_fRad);
	pVtx[4].pos = D3DXVECTOR3(sinf(((D3DX_PI / 4) * 4) + 100.0f)*g_fRad, 0.0f, cosf(((D3DX_PI / 4) * 4) + 100.0f)*g_fRad);
	pVtx[5].pos = D3DXVECTOR3(sinf(((D3DX_PI / 4) * 5) + 100.0f)*g_fRad, 0.0f, cosf(((D3DX_PI / 4) * 5) + 100.0f)*g_fRad);
	pVtx[6].pos = D3DXVECTOR3(sinf(((D3DX_PI / 4) * 6) + 100.0f)*g_fRad, 0.0f, cosf(((D3DX_PI / 4) * 6) + 100.0f)*g_fRad);
	pVtx[7].pos = D3DXVECTOR3(sinf(((D3DX_PI / 4) * 7) + 100.0f)*g_fRad, 0.0f, cosf(((D3DX_PI / 4) * 7) + 100.0f)*g_fRad);
	pVtx[8].pos = D3DXVECTOR3(sinf(((D3DX_PI / 4) * 8) + 100.0f)*g_fRad, 0.0f, cosf(((D3DX_PI / 4) * 8) + 100.0f)*g_fRad);
	pVtx[9].pos = D3DXVECTOR3(sinf(((D3DX_PI / 4) * 0) + 100.0f)*g_fRad, 100.0f, cosf(((D3DX_PI / 4) * 0) + 100.0f)*g_fRad);
	pVtx[10].pos = D3DXVECTOR3(sinf(((D3DX_PI / 4) * 1) + 100.0f)*g_fRad,100.0f, cosf(((D3DX_PI / 4) * 1) + 100.0f)*g_fRad);
	pVtx[11].pos = D3DXVECTOR3(sinf(((D3DX_PI / 4) * 2) + 100.0f)*g_fRad,100.0f, cosf(((D3DX_PI / 4) * 2) + 100.0f)*g_fRad);
	pVtx[12].pos = D3DXVECTOR3(sinf(((D3DX_PI / 4) * 3) + 100.0f)*g_fRad,100.0f, cosf(((D3DX_PI / 4) * 3) + 100.0f)*g_fRad);
	pVtx[13].pos = D3DXVECTOR3(sinf(((D3DX_PI / 4) * 4) + 100.0f)*g_fRad,100.0f, cosf(((D3DX_PI / 4) * 4) + 100.0f)*g_fRad);
	pVtx[14].pos = D3DXVECTOR3(sinf(((D3DX_PI / 4) * 5) + 100.0f)*g_fRad,100.0f, cosf(((D3DX_PI / 4) * 5) + 100.0f)*g_fRad);
	pVtx[15].pos = D3DXVECTOR3(sinf(((D3DX_PI / 4) * 6) + 100.0f)*g_fRad,100.0f, cosf(((D3DX_PI / 4) * 6) + 100.0f)*g_fRad);
	pVtx[16].pos = D3DXVECTOR3(sinf(((D3DX_PI / 4) * 7) + 100.0f)*g_fRad,100.0f, cosf(((D3DX_PI / 4) * 7) + 100.0f)*g_fRad);
	pVtx[17].pos = D3DXVECTOR3(sinf(((D3DX_PI / 4) * 8) + 100.0f)*g_fRad,100.0f, cosf(((D3DX_PI / 4) * 8) + 100.0f)*g_fRad);


	//法線ベクトルの設定
	for (int nCnt = 0; nCnt < (g_nSplitBesideCylinder * g_nSplitVerticalCylinder); nCnt++)
	{
		pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	}

	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[8].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点カラーの設定

	for (int nCnt = 0; nCnt < (g_nSplitBesideCylinder * g_nSplitVerticalCylinder); nCnt++)
	{
		pVtx[nCnt].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	}


	g_pVtxBuffMeshCylinder->Unlock();

	WORD*pIdx; //インデックス情報へのポインタ
			   //インデックスバッファをロックし、頂点番号データへのポインタを取得
	g_pIdxBuffMeshCylinder->Lock(0, 0, (void**)&pIdx, 0);
	int nCnt1;
	int nCnt2;
	int nPlus = 0;

	

	//頂点番号データの設定
	pIdx[0] = 0;
	pIdx[1] = 9;
	pIdx[2] = 1;
	pIdx[3] = 10;
	pIdx[4] = 2;
	pIdx[5] = 11;
	pIdx[6] = 3;
	pIdx[7] = 12;
	pIdx[8] = 4;
	pIdx[9] = 13;
	pIdx[10] = 5;
	pIdx[11] = 14;
	pIdx[12] = 6;
	pIdx[13] = 15;
	pIdx[14] = 7;
	pIdx[15] = 16;
	pIdx[16] = 8;
	pIdx[17] = 17;
	g_pIdxBuffMeshCylinder->Unlock();
}




//プレイヤーの終了処理
void UninitMeshCylinder(void)
{
	if (g_pTextureMeshCylinder != NULL)
	{
		g_pTextureMeshCylinder->Release();
		g_pTextureMeshCylinder = NULL;
	}
	if (g_pVtxBuffMeshCylinder != NULL)
	{
		g_pVtxBuffMeshCylinder->Release();
		g_pVtxBuffMeshCylinder = NULL;
	}
	if (g_pIdxBuffMeshCylinder != NULL)
	{
		g_pIdxBuffMeshCylinder->Release();
		g_pIdxBuffMeshCylinder = NULL;
	}
}

//プレイヤーの更新処理
void UpdateMeshCylinder(void)
{

}

//プレイヤーの描画処理
void DrawMeshCylinder(void)
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ
	pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans; //計算用マトリクス

								 //ワールドマトリクスの初期化
	D3DXMatrixIdentity(&g_mtxWorldMeshCylinder);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshCylinder.y, g_rotMeshCylinder.x, g_rotMeshCylinder.z);

	D3DXMatrixMultiply(&g_mtxWorldMeshCylinder, &g_mtxWorldMeshCylinder, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_posMeshCylinder.x, g_posMeshCylinder.y, g_posMeshCylinder.z);

	D3DXMatrixMultiply(&g_mtxWorldMeshCylinder, &g_mtxWorldMeshCylinder, &mtxTrans);

	//ワールドマトリクスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshCylinder);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffMeshCylinder, 0, sizeof(VERTEX_3D));

	//インデックスバッファをデータストリームに設定
	pDevice->SetIndices(g_pIdxBuffMeshCylinder);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureMeshCylinder);


	//ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, (2 * g_nSplitVerticalCylinder), 0, (g_nSplitVerticalCylinder * 2 * (g_nSplitBesideCylinder - 1) ));

}