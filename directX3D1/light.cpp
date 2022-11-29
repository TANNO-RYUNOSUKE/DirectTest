#include "light.h"

D3DLIGHT9 g_light[3];

void InitLight()
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ
	pDevice = GetDevice();

	D3DXVECTOR3 vecDir; //設定用方向ベクトル

	for (int nCntTex = 0; nCntTex < 3; nCntTex++)
	{
		//ライトの情報をクリアする
		ZeroMemory(&g_light, sizeof(D3DLIGHT9));
		//ライトの種類の設定
		g_light[nCntTex].Type = D3DLIGHT_DIRECTIONAL;

		//ライトの拡散光を設定
		g_light[nCntTex].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//ライトの方向を設定
		vecDir = D3DXVECTOR3(0.2f - (0.2f * nCntTex), -1.0f + (0.2f * nCntTex), 0.7f + (0.1f * nCntTex));
		D3DXVec3Normalize(&vecDir, &vecDir);
		g_light[nCntTex].Direction = vecDir;

		//ライトを設定する
		pDevice->SetLight(0, &g_light[nCntTex]);

	}
	//ライトを有効にする
	pDevice->LightEnable(0, TRUE);
}
void UninitLight()
{

}
void UpdateLight()
{

}