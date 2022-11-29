#include "particle.h"
#include "Effect.h"

#define MAX_PARTICLE (128)

typedef struct
{
	D3DXVECTOR3 pos; //�ʒu
	D3DXVECTOR3 move; //�ړ���
	D3DXCOLOR col; //�F
	float fRadius; //���a
	int nLife; //����
	bool bUse; //�g�p���Ă��邩
}Particle;

Particle g_aParticle[MAX_PARTICLE];

void InitParticle()
{
	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		g_aParticle[nCntParticle].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle[nCntParticle].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle[nCntParticle].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aParticle[nCntParticle].bUse = false;
	}
}
void UninitParticle()
{

}
void UpdateParticle()
{
	float fRot;//�p�x
	float fMove;//�ړ���
	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (g_aParticle[nCntParticle].bUse == true)
		{
			for (int nCntAppear = 0; nCntAppear < 2; nCntAppear++)
			{
				g_aParticle[nCntParticle].nLife--;
				fRot = (float)(rand() % 629 - 314) / 100.0f;
				fMove = (float)(rand() % 100) / 10.0f + 2.0f;
				g_aParticle[nCntParticle].move.x = sinf(fRot)*fMove;
				g_aParticle[nCntParticle].move.y = cosf(fRot)*fMove;
				g_aParticle[nCntParticle].col = D3DXCOLOR(0.8f, 0.5f, 0.5f, 1.0f);

				SetEffect(g_aParticle[nCntParticle].pos, g_aParticle[nCntParticle].col, g_aParticle[nCntParticle].move, 10.0f, 120);
				
				if (g_aParticle[nCntParticle].nLife <= 0)
				{
					g_aParticle[nCntParticle].bUse = false;
				}
			}
		}
	}
}
void DrawParticle()
{

}
void SetParticle(D3DXVECTOR3 pos,int nLife, int nType)
{
	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (g_aParticle[nCntParticle].bUse == false)
		{
			g_aParticle[nCntParticle].pos = pos;
			g_aParticle[nCntParticle].nLife = nLife;
			g_aParticle[nCntParticle].bUse = true;
			break;
		}
	}
}
