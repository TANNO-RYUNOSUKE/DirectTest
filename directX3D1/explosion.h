
//==================
//爆発処理
//==================
#ifndef _Explosion_H_
#define _Explosion_H_
#include "main.h"

//プロトタイプ宣言
void InitExplosion();
void UninitExplosion();
void UpdateExplosion();
void DrawExplosion();
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col);

#endif // !_Explosion_H_
