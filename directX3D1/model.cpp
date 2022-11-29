#include "model.h"
#include "shadow.h"
#include "input.h"

//マクロ定義
#define MOVE_SPEED (5.0f)

//グローバル変数

LPD3DXMESH g_pMeshModel = NULL; //メッシュ(頂点情報)へのポインタ
LPD3DXBUFFER g_pBuffMatModel = NULL; //マテリアルへのポインタ
DWORD g_dwNumMatModel = 0; //マテリアルの数
D3DXVECTOR3 g_posModel; //位置
D3DXVECTOR3 g_rotModel; //向き
D3DXVECTOR3 g_vtxMinModel, g_vtxMaxModel;
D3DXMATRIX g_mtxWorldModel; //ワールドマトリクス
LPDIRECT3DTEXTURE9 g_pTextureModel[8] = {};
int g_nIndexShadow;

void InitModel()
{
	int nNumVtx; //頂点数
	DWORD dwSizeFVF; //頂点フォーマットのサイズ
	BYTE*pVtxBuff; //頂点バッファへのポインタ
	LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ
	pDevice = GetDevice();

	g_posModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_vtxMinModel = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);
	g_vtxMaxModel = D3DXVECTOR3(-1000.0f, -1000.0f, -1000.0f);
	g_nIndexShadow = SetShadow();

	//xファイルの読み込み
	D3DXLoadMeshFromX("Data\\MODEL\\AbandonedBuilding.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatModel,
		NULL,
		&g_dwNumMatModel,
		&g_pMeshModel);

	//頂点数を取得
	nNumVtx = g_pMeshModel->GetNumVertices();

	//頂点フォーマットのサイズを取得
	dwSizeFVF = D3DXGetFVFVertexSize(g_pMeshModel->GetFVF());

	//頂点バッファをロック
	g_pMeshModel->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;
		if (g_vtxMinModel.x > vtx.x)
		{
			g_vtxMinModel.x = vtx.x;
		}
		if (g_vtxMinModel.y > vtx.y)
		{
			g_vtxMinModel.y = vtx.y;
		}
		if (g_vtxMinModel.z > vtx.z)
		{
			g_vtxMinModel.z = vtx.z;
		}
		if (g_vtxMaxModel.x < vtx.x)
		{
			g_vtxMaxModel.x = vtx.x;
		}
		if (g_vtxMaxModel.y < vtx.y)
		{
			g_vtxMaxModel.y = vtx.y;
		}
		if (g_vtxMaxModel.z < vtx.z)
		{
			g_vtxMaxModel.z = vtx.z;
		}
		
		pVtxBuff += dwSizeFVF;
	}
	//頂点バッファをアンロック
	g_pMeshModel->UnlockVertexBuffer();

	//テクスチャの読み込み
	D3DXMATERIAL *pMat; //マテリアルデータへのポインタ
	pMat = (D3DXMATERIAL*)g_pBuffMatModel->GetBufferPointer();
	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatModel; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{//テクスチャファイルが存在する時
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_pTextureModel[nCntMat]);
		}
	}
}
void UninitModel()
{
	for (int nCntTex = 0; nCntTex < 8; nCntTex++)
	{
		if (g_pTextureModel[nCntTex] != NULL)
		{
			g_pTextureModel[nCntTex]->Release();
			g_pTextureModel[nCntTex] = NULL;
		}
	}
	//メッシュの破棄
	if(g_pMeshModel != NULL)
	{
		g_pMeshModel->Release();
		g_pMeshModel = NULL;
	}

	//マテリアルの破棄
	if (g_pBuffMatModel != NULL)
	{
		g_pBuffMatModel->Release();
		g_pBuffMatModel = NULL;
	}
}
void UpdateModel()
{
	//移動
	/*if (GetKeyboardPress(DIK_UP) == true)
	{
		g_posModel.z += MOVE_SPEED;
	}
	if (GetKeyboardPress(DIK_DOWN) == true)
	{
		g_posModel.z -= MOVE_SPEED;
	}
	if (GetKeyboardPress(DIK_LEFT) == true)
	{
		g_posModel.x -= MOVE_SPEED;
	}
	if (GetKeyboardPress(DIK_RIGHT) == true)
	{
		g_posModel.x += MOVE_SPEED;
	}*/
	//影の位置
	SetPositionShadow(g_nIndexShadow, g_posModel);
}
void DrawModel()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice(); //デバイスのポインタ
	D3DXMATRIX mtxRot, mtxTrans; //計算用マトリクス
	D3DMATERIAL9 matDef; //現在のマテリアル保存用
	D3DXMATERIAL *pMat; //マテリアルデータへのポインタ

	//ワールドマトリクスの初期化
	D3DXMatrixIdentity(&g_mtxWorldModel);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotModel.y, g_rotModel.x, g_rotModel.z);
	D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_posModel.x, g_posModel.y, g_posModel.z);
	D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxTrans);

	//ワールドマトリクスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldModel);

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	//マテリアルデータのポインタを取得
	pMat = (D3DXMATERIAL*)g_pBuffMatModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatModel; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureModel[nCntMat]);

		//モデル(パーツ)の描写
		g_pMeshModel->DrawSubset(nCntMat);
	}
	//保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}
