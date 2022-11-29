#include "main.h"
#include "Billborad.h"

//�}�N����`
#define MAX_BILLBORAD (255)

//�O���[�o���ϐ�

LPDIRECT3DTEXTURE9 g_pTextureBillborad = NULL; //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBillborad = NULL; //���_�o�b�t�@�ւ̃|�C���^

BILLBORAD g_aBillborad[MAX_BILLBORAD];

void InitBillborad(void)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = GetDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"Data\\TEXTURE\\Bullet000.png",
		&g_pTextureBillborad);

	for (int nCnt = 0; nCnt < MAX_BILLBORAD; nCnt++)
	{
		g_aBillborad[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBillborad[nCnt].bUse = false;
	}
	
	

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BILLBORAD,
		D3DUSAGE_WRITEONLY,
		{ FVF_VERTEX_3D },
		D3DPOOL_MANAGED,
		&g_pVtxBuffBillborad,
		NULL);

	VERTEX_3D * pVtx;
	g_pVtxBuffBillborad->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_BILLBORAD; nCnt++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-100.0f, +100.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(+100.0f, +100.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-100.0f, -100.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(+100.0f, -100.0f, 0.0f);

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

	g_pVtxBuffBillborad->Unlock();

	SetBillborad(D3DXVECTOR3(0.0f, 0.0f, -1.0f), 0.0f);
	SetBillborad(D3DXVECTOR3(+100.0f, 0.0f,0.0f), 0.0f);
}




//�v���C���[�̏I������
void UninitBillborad(void)
{
	if (g_pTextureBillborad != NULL)
	{
		g_pTextureBillborad->Release();
		g_pTextureBillborad = NULL;
	}
	if (g_pVtxBuffBillborad != NULL)
	{
		g_pVtxBuffBillborad->Release();
		g_pVtxBuffBillborad = NULL;
	}
}

//�v���C���[�̍X�V����
void UpdateBillborad(void)
{
	VERTEX_3D * pVtx;
	g_pVtxBuffBillborad->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCnt = 0; nCnt < MAX_BILLBORAD; nCnt++)
	{
		if (g_aBillborad[nCnt].bUse == true)
		{
			//���_���W�̐ݒ�
			

		}
		pVtx += 4;
	}
}

//�v���C���[�̕`�揈��
void DrawBillborad(void)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = GetDevice();

	D3DXMATRIX  mtxTrans; //�v�Z�p�}�g���N�X
	D3DXMATRIX mtxView; //�r���[�}�g���N�X�擾�p

	//�A���t�@�e�X�g��L����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 80);

	//Z�e�X�g�𖳌���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	for (int nCnt = 0; nCnt < MAX_BILLBORAD; nCnt++)
	{
		if (g_aBillborad[nCnt].bUse == true)
		{
			//���[���h�}�g���N�X�̏�����
			D3DXMatrixIdentity(&g_aBillborad[nCnt].mtx);

			//�r���[�}�g���N�X�擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
			D3DXMatrixInverse(&g_aBillborad[nCnt].mtx, NULL, &mtxView);

			g_aBillborad[nCnt].mtx._41 = 0.0f;
			g_aBillborad[nCnt].mtx._42 = 0.0f;
			g_aBillborad[nCnt].mtx._43 = 0.0f;

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aBillborad[nCnt].pos.x, g_aBillborad[nCnt].pos.y, g_aBillborad[nCnt].pos.z);

			D3DXMatrixMultiply(&g_aBillborad[nCnt].mtx, &g_aBillborad[nCnt].mtx, &mtxTrans);

			//���[���h�}�g���N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aBillborad[nCnt].mtx);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffBillborad, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureBillborad);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,nCnt * 4 , 2);
		}
	}
	//Z�e�X�g��L����
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//�A���t�@�e�X�g�𖳌���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 80);
}

void SetBillborad(D3DXVECTOR3 pos, float fRadius)
{
	
	for (int nCnt = 0; nCnt < MAX_BILLBORAD; nCnt++)
	{
		if (g_aBillborad[nCnt].bUse == false)
		{
			g_aBillborad[nCnt].pos = pos;
			g_aBillborad[nCnt].fRadius = fRadius;
			g_aBillborad[nCnt].bUse = true;
			break;
		}
	
	}

}