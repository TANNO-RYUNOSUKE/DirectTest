#ifndef _Wall_H_
#define _Wall_H_
#include "main.h"

//構造体宣言
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXMATRIX  mtx;
	float fRadius;
	bool bUse;
}WALL;
//プロトタイプ宣言
void InitWall();
void UninitWall();
void UpdateWall();
void DrawWall();

#endif // !_Wall_H_
