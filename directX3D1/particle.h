//==================
//�p�[�e�B�N������
//==================
#ifndef _Particle_H_
#define _Particle_H_
#include "main.h"

//�v���g�^�C�v�錾
void InitParticle();
void UninitParticle();
void UpdateParticle();
void DrawParticle();
void SetParticle(D3DXVECTOR3 pos,  int nLife, int nType);

#endif // !_Particle_H_