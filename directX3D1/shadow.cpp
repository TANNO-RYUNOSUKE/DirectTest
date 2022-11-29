#include "main.h"
#include "Shadow.h"

//�}�N����`
#define MAX_SHADOW (256)

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureShadow = NULL; //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL; //���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posShadow;
D3DXVECTOR3 g_rotShadow;
D3DXMATRIX g_mtxWorldShadow;
SHADOW g_Shadow[MAX_SHADOW];

void InitShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = GetDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"Data\\TEXTURE\\shadow000.jpg",
		&g_pTextureShadow);
	
	for (int nCnt = 0; nCnt < MAX_SHADOW; nCnt++)
	{
		g_Shadow[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Shadow[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Shadow[nCnt].fRadius = 30.0f;
		g_Shadow[nCnt].bUse = false;
	}
	

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_SHADOW,
		D3DUSAGE_WRITEONLY,
		{ FVF_VERTEX_3D },
		D3DPOOL_MANAGED,
		&g_pVtxBuffShadow,
		NULL);

	VERTEX_3D * pVtx;
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCnt = 0; nCnt < MAX_SHADOW; nCnt++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-g_Shadow[nCnt].fRadius, 0.0f, +g_Shadow[nCnt].fRadius);
		pVtx[1].pos = D3DXVECTOR3(+g_Shadow[nCnt].fRadius, 0.0f, +g_Shadow[nCnt].fRadius);
		pVtx[2].pos = D3DXVECTOR3(-g_Shadow[nCnt].fRadius, 0.0f, -g_Shadow[nCnt].fRadius);
		pVtx[3].pos = D3DXVECTOR3(+g_Shadow[nCnt].fRadius, 0.0f, -g_Shadow[nCnt].fRadius);

		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		pVtx += 4;
	}
	g_pVtxBuffShadow->Unlock();
}




//�v���C���[�̏I������
void UninitShadow(void)
{
	if (g_pTextureShadow != NULL)
	{
		g_pTextureShadow->Release();
		g_pTextureShadow = NULL;
	}
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}
}

//�v���C���[�̍X�V����
void UpdateShadow(void)
{

}

//�v���C���[�̕`�揈��
void DrawShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���N�X

	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	for (int nCnt = 0; nCnt < MAX_SHADOW; nCnt++)
	{
		if (g_Shadow[nCnt].bUse == true)
		{
			//���[���h�}�g���N�X�̏�����
			D3DXMatrixIdentity(&g_Shadow[nCnt].mtx);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Shadow[nCnt].rot.y, g_Shadow[nCnt].rot.x, g_Shadow[nCnt].rot.z);

			D3DXMatrixMultiply(&g_Shadow[nCnt].mtx, &g_Shadow[nCnt].mtx, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Shadow[nCnt].pos.x, g_Shadow[nCnt].pos.y, g_Shadow[nCnt].pos.z);

			D3DXMatrixMultiply(&g_Shadow[nCnt].mtx, &g_Shadow[nCnt].mtx, &mtxTrans);

			//���[���h�}�g���N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Shadow[nCnt].mtx);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureShadow);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
			
		}
	}
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

int SetShadow()
{
	int nCnt;
	for ( nCnt = 0; nCnt < MAX_SHADOW; nCnt++)
	{
		if (g_Shadow[nCnt].bUse == false)
		{
			g_Shadow[nCnt].bUse = true;
			return nCnt;
		}
	}
	return -1;
}
void SetPositionShadow(int nIndexShadow, D3DXVECTOR3 pos)
{
	if (nIndexShadow >= 0)
	{
		g_Shadow[nIndexShadow].pos.x = pos.x;
		g_Shadow[nIndexShadow].pos.z = pos.z;
	
	}
}

void DelShadow(int nIndex)
{
	g_Shadow[nIndex].bUse = false;
}