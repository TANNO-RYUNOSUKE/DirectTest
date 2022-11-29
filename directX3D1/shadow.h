#ifndef _Shadow_H_
#define _Shadow_H_
#include "main.h"

//構造体宣言
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXMATRIX  mtx;
	float fRadius;
	bool bUse;
}SHADOW;
//プロトタイプ宣言
void InitShadow();
void UninitShadow();
void UpdateShadow();
void DrawShadow();
int SetShadow();

void DelShadow(int nIndex);
void SetPositionShadow(int nIndexShadow, D3DXVECTOR3 pos);

#endif // !_Shadow_H_

