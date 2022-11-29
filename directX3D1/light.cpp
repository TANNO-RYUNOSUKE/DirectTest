#include "light.h"

D3DLIGHT9 g_light[3];

void InitLight()
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = GetDevice();

	D3DXVECTOR3 vecDir; //�ݒ�p�����x�N�g��

	for (int nCntTex = 0; nCntTex < 3; nCntTex++)
	{
		//���C�g�̏����N���A����
		ZeroMemory(&g_light, sizeof(D3DLIGHT9));
		//���C�g�̎�ނ̐ݒ�
		g_light[nCntTex].Type = D3DLIGHT_DIRECTIONAL;

		//���C�g�̊g�U����ݒ�
		g_light[nCntTex].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//���C�g�̕�����ݒ�
		vecDir = D3DXVECTOR3(0.2f - (0.2f * nCntTex), -1.0f + (0.2f * nCntTex), 0.7f + (0.1f * nCntTex));
		D3DXVec3Normalize(&vecDir, &vecDir);
		g_light[nCntTex].Direction = vecDir;

		//���C�g��ݒ肷��
		pDevice->SetLight(0, &g_light[nCntTex]);

	}
	//���C�g��L���ɂ���
	pDevice->LightEnable(0, TRUE);
}
void UninitLight()
{

}
void UpdateLight()
{

}