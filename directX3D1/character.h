#include "main.h"
#ifndef _Character_H_
#define _Character_H_

//�\����

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 rotDest;
	D3DXVECTOR3 move;
	D3DXMATRIX  mtx;
	int InputCount;
	int nIndexShadow;
	bool bUse;
}characte;

//�v���g�^�C�v�錾
void InitCharacter();
void UninitCharacter();
void UpdateCharacter();
void DrawCharacter();
characte Getcharacte();

#endif // !_Character_H_
