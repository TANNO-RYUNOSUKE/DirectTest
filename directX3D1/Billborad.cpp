#include "main.h"
#include "Billborad.h"

//マクロ定義
#define MAX_BILLBORAD (255)

//グローバル変数

LPDIRECT3DTEXTURE9 g_pTextureBillborad = NULL; //テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBillborad = NULL; //頂点バッファへのポインタ

BILLBORAD g_aBillborad[MAX_BILLBORAD];

void InitBillborad(void)
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ
	pDevice = GetDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		"Data\\TEXTURE\\Bullet000.png",
		&g_pTextureBillborad);

	for (int nCnt = 0; nCnt < MAX_BILLBORAD; nCnt++)
	{
		g_aBillborad[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBillborad[nCnt].bUse = false;
	}
	
	

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BILLBORAD,
		D3DUSAGE_WRITEONLY,
		{ FVF_VERTEX_3D },
		D3DPOOL_MANAGED,
		&g_pVtxBuffBillborad,
		NULL);

	VERTEX_3D * pVtx;
	g_pVtxBuffBillborad->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_BILLBORAD; nCnt++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-100.0f, +100.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(+100.0f, +100.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-100.0f, -100.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(+100.0f, -100.0f, 0.0f);

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

	g_pVtxBuffBillborad->Unlock();

	SetBillborad(D3DXVECTOR3(0.0f, 0.0f, -1.0f), 0.0f);
	SetBillborad(D3DXVECTOR3(+100.0f, 0.0f,0.0f), 0.0f);
}




//プレイヤーの終了処理
void UninitBillborad(void)
{
	if (g_pTextureBillborad != NULL)
	{
		g_pTextureBillborad->Release();
		g_pTextureBillborad = NULL;
	}
	if (g_pVtxBuffBillborad != NULL)
	{
		g_pVtxBuffBillborad->Release();
		g_pVtxBuffBillborad = NULL;
	}
}

//プレイヤーの更新処理
void UpdateBillborad(void)
{
	VERTEX_3D * pVtx;
	g_pVtxBuffBillborad->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCnt = 0; nCnt < MAX_BILLBORAD; nCnt++)
	{
		if (g_aBillborad[nCnt].bUse == true)
		{
			//頂点座標の設定
			

		}
		pVtx += 4;
	}
}

//プレイヤーの描画処理
void DrawBillborad(void)
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ
	pDevice = GetDevice();

	D3DXMATRIX  mtxTrans; //計算用マトリクス
	D3DXMATRIX mtxView; //ビューマトリクス取得用

	//アルファテストを有効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 80);

	//Zテストを無効化
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	for (int nCnt = 0; nCnt < MAX_BILLBORAD; nCnt++)
	{
		if (g_aBillborad[nCnt].bUse == true)
		{
			//ワールドマトリクスの初期化
			D3DXMatrixIdentity(&g_aBillborad[nCnt].mtx);

			//ビューマトリクス取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//ポリゴンをカメラに対して正面に向ける
			D3DXMatrixInverse(&g_aBillborad[nCnt].mtx, NULL, &mtxView);

			g_aBillborad[nCnt].mtx._41 = 0.0f;
			g_aBillborad[nCnt].mtx._42 = 0.0f;
			g_aBillborad[nCnt].mtx._43 = 0.0f;

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aBillborad[nCnt].pos.x, g_aBillborad[nCnt].pos.y, g_aBillborad[nCnt].pos.z);

			D3DXMatrixMultiply(&g_aBillborad[nCnt].mtx, &g_aBillborad[nCnt].mtx, &mtxTrans);

			//ワールドマトリクスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aBillborad[nCnt].mtx);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffBillborad, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureBillborad);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,nCnt * 4 , 2);
		}
	}
	//Zテストを有効化
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//アルファテストを無効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 80);
}

void SetBillborad(D3DXVECTOR3 pos, float fRadius)
{
	
	for (int nCnt = 0; nCnt < MAX_BILLBORAD; nCnt++)
	{
		if (g_aBillborad[nCnt].bUse == false)
		{
			g_aBillborad[nCnt].pos = pos;
			g_aBillborad[nCnt].fRadius = fRadius;
			g_aBillborad[nCnt].bUse = true;
			break;
		}
	
	}

}