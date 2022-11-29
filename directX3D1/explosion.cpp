#include "Explosion.h"
#include "Effect.h"


//プロトタイプ宣言
#define MAX_Explosion (1280)

//構造体を宣言
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXCOLOR col;
	D3DXMATRIX  mtx;
	int nCounterAnim;
	int nPatternAnim;
	bool bUse;
}Explosion;

//グローバル変数
D3DXVECTOR3 g_rotExplosion;
float g_fLengthExplosion;
float g_fAngleExplosion;


LPDIRECT3DTEXTURE9 g_pTextureExplosion = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;
Explosion g_aExplosion[MAX_Explosion];

//======================================
//初期化処理
//======================================
void InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntExplosion;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		"Data\\TEXTURE\\Explosion000.png",
		&g_pTextureExplosion);

	//弾の情報の初期化
	for (nCntExplosion = 0; nCntExplosion < MAX_Explosion; nCntExplosion++)
	{
		g_aExplosion[nCntExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCntExplosion].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aExplosion[nCntExplosion].nCounterAnim = 0;
		g_aExplosion[nCntExplosion].nPatternAnim = 0;
		g_aExplosion[nCntExplosion].bUse = false;
	}
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_Explosion,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffExplosion,
		NULL);

	VERTEX_3D *pVtx;
	//頂点バッファをロックし、頂点データへのポインタ
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_Explosion; nCntExplosion++)
	{
		//頂点座標の設定
		pVtx[0].pos.x = g_aExplosion[nCntExplosion].pos.x + sinf(g_rotExplosion.z - g_fAngleExplosion)*g_fLengthExplosion;
		pVtx[0].pos.y = g_aExplosion[nCntExplosion].pos.y + cosf(g_rotExplosion.z - g_fAngleExplosion)*g_fLengthExplosion;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_aExplosion[nCntExplosion].pos.x + sinf(g_rotExplosion.z + g_fAngleExplosion)*g_fLengthExplosion;
		pVtx[1].pos.y = g_aExplosion[nCntExplosion].pos.y + cosf(g_rotExplosion.z - g_fAngleExplosion)*g_fLengthExplosion;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_aExplosion[nCntExplosion].pos.x + sinf(g_rotExplosion.z - g_fAngleExplosion)*g_fLengthExplosion;
		pVtx[2].pos.y = g_aExplosion[nCntExplosion].pos.y + cosf(g_rotExplosion.z + g_fAngleExplosion)*g_fLengthExplosion;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_aExplosion[nCntExplosion].pos.x + sinf(g_rotExplosion.z + g_fAngleExplosion)*g_fLengthExplosion;
		pVtx[3].pos.y = g_aExplosion[nCntExplosion].pos.y + cosf(g_rotExplosion.z + g_fAngleExplosion)*g_fLengthExplosion;
		pVtx[3].pos.z = 0.0f;

	

		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	g_pVtxBuffExplosion->Unlock();
}

//======================================
//終了処理
//======================================
void UninitExplosion(void)
{
	if (g_pTextureExplosion != NULL)
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}
	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}
}
//======================================
//更新処理
//======================================
void UpdateExplosion(void)
{
	int nCntExplosion;
	VERTEX_3D *pVtx;
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_Explosion; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)
		{//弾が使用されている
	g_aExplosion[nCntExplosion].nCounterAnim++;
	if (g_aExplosion[nCntExplosion].nCounterAnim % 4 == 0)
	{
		g_aExplosion[nCntExplosion].nPatternAnim = (g_aExplosion[nCntExplosion].nPatternAnim + 1);
	}
			pVtx[0].pos = D3DXVECTOR3((- 60), (+ 60), 0.0f);
			pVtx[1].pos = D3DXVECTOR3((+ 60), (+ 60), 0.0f);
			pVtx[2].pos = D3DXVECTOR3((- 60), (- 60), 0.0f);
			pVtx[3].pos = D3DXVECTOR3((+ 60), (- 60), 0.0f);
			pVtx[0].tex = D3DXVECTOR2(((g_aExplosion[nCntExplosion].nPatternAnim) * 0.125f), 0.0f);
			pVtx[1].tex = D3DXVECTOR2(((g_aExplosion[nCntExplosion].nPatternAnim + 1) * 0.125f), 0.0f);
			pVtx[2].tex = D3DXVECTOR2(((g_aExplosion[nCntExplosion].nPatternAnim) * 0.125f), 1.0f);
			pVtx[3].tex = D3DXVECTOR2(((g_aExplosion[nCntExplosion].nPatternAnim + 1) * 0.125f), 1.0f);
		
			if (g_aExplosion[nCntExplosion].nPatternAnim > 8)
			{
				g_aExplosion[nCntExplosion].bUse = false;
			}

		}pVtx += 4;
	}

g_pVtxBuffExplosion->Unlock();
}
	
//======================================
//描画処理
//======================================
void DrawExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ
	pDevice = GetDevice();

	D3DXMATRIX  mtxTrans; //計算用マトリクス
	D3DXMATRIX mtxView; //ビューマトリクス取得用

						//アルファテストを有効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 80);
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//Zテストを無効化
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	for (int nCnt = 0; nCnt < MAX_Explosion; nCnt++)
	{
		if (g_aExplosion[nCnt].bUse == true)
		{
			//ワールドマトリクスの初期化
			D3DXMatrixIdentity(&g_aExplosion[nCnt].mtx);

			//ビューマトリクス取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//ポリゴンをカメラに対して正面に向ける
			D3DXMatrixInverse(&g_aExplosion[nCnt].mtx, NULL, &mtxView);

			g_aExplosion[nCnt].mtx._41 = 0.0f;
			g_aExplosion[nCnt].mtx._42 = 0.0f;
			g_aExplosion[nCnt].mtx._43 = 0.0f;

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aExplosion[nCnt].pos.x, g_aExplosion[nCnt].pos.y, g_aExplosion[nCnt].pos.z);

			D3DXMatrixMultiply(&g_aExplosion[nCnt].mtx, &g_aExplosion[nCnt].mtx, &mtxTrans);

			//ワールドマトリクスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aExplosion[nCnt].mtx);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureExplosion);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
		}
	}
	//Zテストを有効化
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//アルファテストを無効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 80);
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}
//======================================
//設定処理
//======================================
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col)
{
	
	int nCntExplosion;
	VERTEX_3D *pVtx;
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_Explosion; nCntExplosion++)
	{


		if (g_aExplosion[nCntExplosion].bUse == false)
		{
			g_aExplosion[nCntExplosion].nPatternAnim = 0;
			g_aExplosion[nCntExplosion].nCounterAnim = 0;
			g_aExplosion[nCntExplosion].pos = pos;
			g_aExplosion[nCntExplosion].col = col;

			pVtx[0].pos = D3DXVECTOR3((- 60), (+ 60), 0.0f);
			pVtx[1].pos = D3DXVECTOR3((+ 60), (+ 60), 0.0f);
			pVtx[2].pos = D3DXVECTOR3((- 60), (- 60), 0.0f);
			pVtx[3].pos = D3DXVECTOR3((+ 60), (- 60), 0.0f);

			pVtx[0].col = g_aExplosion[nCntExplosion].col;
			pVtx[1].col = g_aExplosion[nCntExplosion].col;
			pVtx[2].col = g_aExplosion[nCntExplosion].col;
			pVtx[3].col = g_aExplosion[nCntExplosion].col;
			SetEffect(g_aExplosion[nCntExplosion].pos, D3DXCOLOR(0.8f, 0.5f, 0.5f, 1.0f),D3DXVECTOR3(0.0f,0.0f,0.0f), 20.0f, 80);
			g_aExplosion[nCntExplosion].bUse = true;
			break;
		}

		pVtx += 4;
	}
	g_pVtxBuffExplosion->Unlock();
}

