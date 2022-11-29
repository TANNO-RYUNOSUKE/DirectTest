#ifndef _Wall_H_
#define _Wall_H_
#include "main.h"

//�\���̐錾
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXMATRIX  mtx;
	float fRadius;
	bool bUse;
}WALL;
//�v���g�^�C�v�錾
void InitWall();
void UninitWall();
void UpdateWall();
void DrawWall();

#endif // !_Wall_H_
