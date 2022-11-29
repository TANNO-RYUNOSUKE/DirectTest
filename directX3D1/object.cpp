#include "Object.h"
#include "shadow.h"
#include "input.h"

//マクロ定義
#define MOVE_SPEED (5.0f)
#define MAX_OBJECT (24)

//グローバル変数

LPD3DXMESH g_pMeshObject = NULL; //メッシュ(頂点情報)へのポインタ
LPD3DXBUFFER g_pBuffMatObject = NULL; //マテリアルへのポインタ
DWORD g_dwNumMatObject = 0; //マテリアルの数
D3DXVECTOR3 g_posObject; //位置
D3DXVECTOR3 g_rotObject; //向き
D3DXVECTOR3 g_vtxMinObject, g_vtxMaxObject;
D3DXMATRIX g_mtxWorldObject; //ワールドマトリクス
LPDIRECT3DTEXTURE9 g_pTextureObject[8] = {};
int g_nIndexShadow;

Object g_aObject[MAX_OBJECT];

void InitObject()
{
	int nNumVtx; //頂点数
	DWORD dwSizeFVF; //頂点フォーマットのサイズ
	BYTE*pVtxBuff; //頂点バッファへのポインタ
	LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ
	pDevice = GetDevice();

	g_posObject = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotObject = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_vtxMinObject = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);
	g_vtxMaxObject = D3DXVECTOR3(-1000.0f, -1000.0f, -1000.0f);
	g_nIndexShadow = SetShadow();

	//xファイルの読み込み
	D3DXLoadMeshFromX("Data\\Object\\AbandonedBuilding.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatObject,
		NULL,
		&g_dwNumMatObject,
		&g_pMeshObject);

	//頂点数を取得
	nNumVtx = g_pMeshObject->GetNumVertices();

	//頂点フォーマットのサイズを取得
	dwSizeFVF = D3DXGetFVFVertexSize(g_pMeshObject->GetFVF());

	//頂点バッファをロック
	g_pMeshObject->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;
		if (g_vtxMinObject.x > vtx.x)
		{
			g_vtxMinObject.x = vtx.x;
		}
		if (g_vtxMinObject.y > vtx.y)
		{
			g_vtxMinObject.y = vtx.y;
		}
		if (g_vtxMinObject.z > vtx.z)
		{
			g_vtxMinObject.z = vtx.z;
		}
		if (g_vtxMaxObject.x < vtx.x)
		{
			g_vtxMaxObject.x = vtx.x;
		}
		if (g_vtxMaxObject.y < vtx.y)
		{
			g_vtxMaxObject.y = vtx.y;
		}
		if (g_vtxMaxObject.z < vtx.z)
		{
			g_vtxMaxObject.z = vtx.z;
		}

		pVtxBuff += dwSizeFVF;
	}
	//頂点バッファをアンロック
	g_pMeshObject->UnlockVertexBuffer();

	//テクスチャの読み込み
	D3DXMATERIAL *pMat; //マテリアルデータへのポインタ
	pMat = (D3DXMATERIAL*)g_pBuffMatObject->GetBufferPointer();
	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatObject; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{//テクスチャファイルが存在する時
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_pTextureObject[nCntMat]);
		}
	}
}
void UninitObject()
{
	for (int nCntTex = 0; nCntTex < 8; nCntTex++)
	{
		if (g_pTextureObject[nCntTex] != NULL)
		{
			g_pTextureObject[nCntTex]->Release();
			g_pTextureObject[nCntTex] = NULL;
		}
	}
	//メッシュの破棄
	if (g_pMeshObject != NULL)
	{
		g_pMeshObject->Release();
		g_pMeshObject = NULL;
	}

	//マテリアルの破棄
	if (g_pBuffMatObject != NULL)
	{
		g_pBuffMatObject->Release();
		g_pBuffMatObject = NULL;
	}
}
void UpdateObject()
{
	//移動
	/*if (GetKeyboardPress(DIK_UP) == true)
	{
	g_posObject.z += MOVE_SPEED;
	}
	if (GetKeyboardPress(DIK_DOWN) == true)
	{
	g_posObject.z -= MOVE_SPEED;
	}
	if (GetKeyboardPress(DIK_LEFT) == true)
	{
	g_posObject.x -= MOVE_SPEED;
	}
	if (GetKeyboardPress(DIK_RIGHT) == true)
	{
	g_posObject.x += MOVE_SPEED;
	}*/
	//影の位置
	SetPositionShadow(g_nIndexShadow, g_posObject);
}
void DrawObject()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice(); //デバイスのポインタ
	D3DXMATRIX mtxRot, mtxTrans; //計算用マトリクス
	D3DMATERIAL9 matDef; //現在のマテリアル保存用
	D3DXMATERIAL *pMat; //マテリアルデータへのポインタ

						//ワールドマトリクスの初期化
	D3DXMatrixIdentity(&g_mtxWorldObject);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotObject.y, g_rotObject.x, g_rotObject.z);
	D3DXMatrixMultiply(&g_mtxWorldObject, &g_mtxWorldObject, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_posObject.x, g_posObject.y, g_posObject.z);
	D3DXMatrixMultiply(&g_mtxWorldObject, &g_mtxWorldObject, &mtxTrans);

	//ワールドマトリクスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldObject);

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	//マテリアルデータのポインタを取得
	pMat = (D3DXMATERIAL*)g_pBuffMatObject->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatObject; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureObject[nCntMat]);

		//モデル(パーツ)の描写
		g_pMeshObject->DrawSubset(nCntMat);
	}
	//保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}
