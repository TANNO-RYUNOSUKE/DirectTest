#ifndef _Billborad_H_
#define _Billborad_H_
#include "main.h"

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXMATRIX  mtx;
	float fRadius;
	bool bUse;
}BILLBORAD;

//プロトタイプ宣言
void InitBillborad();
void UninitBillborad();
void UpdateBillborad();
void DrawBillborad();
void SetBillborad(D3DXVECTOR3 pos, float fRadius);

#endif // !_Billborad_H_
