#include "main.h"
#ifndef _Object_H_
#define _Object_H_

typedef struct
{
	D3DXVECTOR3 Startpos;	//位置
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 move;		//移動量
	D3DXVECTOR3 rot;		//向き
	D3DXMATRIX mtxWorld;	//ワールドマトリックス
	int nIdxShadow;			//影のインデックス番号
	bool bUse;				//使用しているか
	LPDIRECT3DTEXTURE9 pTexture[30];	//テクスチャへのポインタ
	LPD3DXMESH pMesh;		//メッシュ(頂点情報)へのポインタ
	LPD3DXBUFFER pBuffMat;	//マテリアルへのポインタ
	D3DXMATERIAL pMatData[80];	//マテリアルのデータ
	DWORD dwNumMat;			//マテリアルの数
}Object;

//プロトタイプ宣言
void InitObject();
void UninitObject();
void UpdateObject();
void DrawObject();

#endif // !_Object_H_
