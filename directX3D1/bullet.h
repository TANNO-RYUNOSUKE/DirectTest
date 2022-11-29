
//==================
//�o���b�g����
//==================
#ifndef _BULLET_H_
#define _BULLET_H_
#include "main.h"

//�v���g�^�C�v�錾
#define MAX_BULLET (1280)



//�e�̎��
typedef enum
{
	BULLETTYPE_PLAYER = 0,
	BULLETTYPE_PLAYER2,
	BULLETTYPE_ENEMY,
	BULLETTYPE_MAX
}BULLETTYPE;

typedef enum
{
	SHOTTYPE_NORMAL = 0,
	SHOTTYPE_SCATTER,
	SHOTTYPE_HOMING,
	SHOTTYPE_FIREWORK,
	SHOTTYPE_SETBOM,
	SHOTTYPE_MAX
}SHOTTYPE;

//�\���̂�錾
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 posOld;
	D3DXVECTOR3 move;
	D3DXVECTOR3 rot;
	D3DXMATRIX  mtx;
	int nIndexShadow;
	float fRadius;
	int nPlayer;
	int nLife;
	bool bUse;
	float fSpeed;
	SHOTTYPE type;
}Bullet;

//�v���g�^�C�v�錾
void InitBullet();
void UninitBullet();
void UpdateBullet();
void DrawBullet();
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, float fRadius,int nLife);
Bullet GetBullet(int nNumber);
void DelBullet(int nPlayer);

#endif // !_PLAYR_H_