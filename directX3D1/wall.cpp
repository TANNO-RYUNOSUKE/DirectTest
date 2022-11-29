#include "main.h"
#include "Wall.h"
#include "input.h"

//�}�N����`
#define MAX_WALL (255)

//�O���[�o���ϐ�

LPDIRECT3DTEXTURE9 g_pTextureWall = NULL; //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall = NULL; //���_�o�b�t�@�ւ̃|�C���^
WALL g_Wall[MAX_WALL];

void InitWall(void)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = GetDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"Data\\TEXTURE\\water02.jpg",
		&g_pTextureWall);

	for (int nCnt = 0; nCnt < MAX_WALL; nCnt++)
	{
		g_Wall[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Wall[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Wall[nCnt].bUse = false;
	}
	
	

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_WALL,
		D3DUSAGE_WRITEONLY,
		{ FVF_VERTEX_3D },
		D3DPOOL_MANAGED,
		&g_pVtxBuffWall,
		NULL);

	VERTEX_3D * pVtx;
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCnt = 0; nCnt < MAX_WALL; nCnt++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-300.0f, +600.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(+300.0f, +600.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-300.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(+300.0f, 0.0f, 0.0f);

		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

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
	g_pVtxBuffWall->Unlock();
}




//�v���C���[�̏I������
void UninitWall(void)
{
	if (g_pTextureWall != NULL)
	{
		g_pTextureWall->Release();
		g_pTextureWall = NULL;
	}
	if (g_pVtxBuffWall != NULL)
	{
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}
}

//�v���C���[�̍X�V����
void UpdateWall(void)
{
	
}

//�v���C���[�̕`�揈��
void DrawWall(void)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���N�X

	for (int nCnt = 0; nCnt < MAX_WALL; nCnt++)
	{
		if (g_Wall[nCnt].bUse == true)
		{
			//���[���h�}�g���N�X�̏�����
			D3DXMatrixIdentity(&g_Wall[nCnt].mtx);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Wall[nCnt].rot.y, g_Wall[nCnt].rot.x, g_Wall[nCnt].rot.z);

			D3DXMatrixMultiply(&g_Wall[nCnt].mtx, &g_Wall[nCnt].mtx, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Wall[nCnt].pos.x, g_Wall[nCnt].pos.y, g_Wall[nCnt].pos.z);

			D3DXMatrixMultiply(&g_Wall[nCnt].mtx, &g_Wall[nCnt].mtx, &mtxTrans);

			//���[���h�}�g���N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Wall[nCnt].mtx);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffWall, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureWall);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCnt, 2);
		}
	}
}