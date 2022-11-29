#include "main.h"
#include "Bullet.h"
#include "shadow.h"
#include "Effect.h"
#include "particle.h"
#include "explosion.h"
#include "meshwall.h"

//マクロ定義
#define MAX_Bullet (255)

//グローバル変数

LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL; //テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL; //頂点バッファへのポインタ

Bullet g_aBullet[MAX_Bullet];

void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ
	pDevice = GetDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		"Data\\TEXTURE\\Bullet000.png",
		&g_pTextureBullet);

	for (int nCnt = 0; nCnt < MAX_Bullet; nCnt++)
	{
		g_aBullet[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCnt].bUse = false;
		g_aBullet[nCnt].nIndexShadow = -1;
	}



	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_Bullet,
		D3DUSAGE_WRITEONLY,
		{ FVF_VERTEX_3D },
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	VERTEX_3D * pVtx;
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_Bullet; nCnt++)
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

	g_pVtxBuffBullet->Unlock();

	
}




//プレイヤーの終了処理
void UninitBullet(void)
{
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}

//弾の更新処理
void UpdateBullet(void)
{
	
	for (int nCnt = 0; nCnt < MAX_Bullet; nCnt++)
	{
		if (g_aBullet[nCnt].bUse == true)
		{
			g_aBullet[nCnt].posOld = g_aBullet[nCnt].pos;
			g_aBullet[nCnt].pos.x += sinf(g_aBullet[nCnt].rot.y)*g_aBullet[nCnt].move.z;
			g_aBullet[nCnt].pos.z += cosf(g_aBullet[nCnt].rot.y)*g_aBullet[nCnt].move.z;
			g_aBullet[nCnt].nLife--;
			SetEffect(g_aBullet[nCnt].pos, D3DXCOLOR(0.5f, 0.8f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), g_aBullet[nCnt].fRadius + 5.0f, 80);
			if (g_aBullet[nCnt].nLife <= 0)
			{
				DelShadow(g_aBullet[nCnt].nIndexShadow);
				g_aBullet[nCnt].bUse = false;
				SetParticle(g_aBullet[nCnt].pos, 20, 0);
				SetExplosion(g_aBullet[nCnt].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
			if (CollisionWall(g_aBullet[nCnt].pos, g_aBullet[nCnt].posOld) == true)
			{
				DelShadow(g_aBullet[nCnt].nIndexShadow);
				g_aBullet[nCnt].bUse = false;
				SetParticle(g_aBullet[nCnt].pos, 20, 0);
				SetExplosion(g_aBullet[nCnt].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}

			SetPositionShadow(g_aBullet[nCnt].nIndexShadow, g_aBullet[nCnt].pos);
		}
	
	}
}

//プレイヤーの描画処理
void DrawBullet(void)
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

	for (int nCnt = 0; nCnt < MAX_Bullet; nCnt++)
	{
		if (g_aBullet[nCnt].bUse == true)
		{
			//ワールドマトリクスの初期化
			D3DXMatrixIdentity(&g_aBullet[nCnt].mtx);

			//ビューマトリクス取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//ポリゴンをカメラに対して正面に向ける
			D3DXMatrixInverse(&g_aBullet[nCnt].mtx, NULL, &mtxView);

			g_aBullet[nCnt].mtx._41 = 0.0f;
			g_aBullet[nCnt].mtx._42 = 0.0f;
			g_aBullet[nCnt].mtx._43 = 0.0f;

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aBullet[nCnt].pos.x, g_aBullet[nCnt].pos.y, g_aBullet[nCnt].pos.z);

			D3DXMatrixMultiply(&g_aBullet[nCnt].mtx, &g_aBullet[nCnt].mtx, &mtxTrans);

			//ワールドマトリクスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aBullet[nCnt].mtx);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureBullet);

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

void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, float fRadius, int nLife)
{
	VERTEX_3D * pVtx;
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCnt = 0; nCnt < MAX_Bullet; nCnt++)
	{
		if (g_aBullet[nCnt].bUse == false)
		{
			g_aBullet[nCnt].pos = pos;
			g_aBullet[nCnt].move = move;
			g_aBullet[nCnt].rot = rot;
			g_aBullet[nCnt].fRadius = fRadius;
			g_aBullet[nCnt].nLife = nLife;
			g_aBullet[nCnt].bUse = true;
			g_aBullet[nCnt].nIndexShadow = SetShadow();
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(-fRadius, +fRadius, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(+fRadius, +fRadius, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-fRadius, -fRadius, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(+fRadius, -fRadius, 0.0f);
			break;
		}
		pVtx += 4;
	}
	g_pVtxBuffBullet->Unlock();
}