//==================
//パーティクル処理
//==================
#ifndef _Particle_H_
#define _Particle_H_
#include "main.h"

//プロトタイプ宣言
void InitParticle();
void UninitParticle();
void UpdateParticle();
void DrawParticle();
void SetParticle(D3DXVECTOR3 pos,  int nLife, int nType);

#endif // !_Particle_H_