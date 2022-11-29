#include "main.h"
#include "MeshWall.h"

//�O���[�o���ϐ�

LPDIRECT3DTEXTURE9 g_pTextureMeshWall = NULL; //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshWall = NULL; //���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshWall = NULL; //�C���f�b�N�X�o�b�t�@�ւ̃|�C���^

D3DXVECTOR3 g_posMeshWall;
D3DXVECTOR3 g_rotMeshWall;
D3DXMATRIX g_mtxWorldMeshWall;
int g_nSplitBesideWall;
int g_nSplitVerticalWall;
float g_fWidthWall;

void InitMeshWall(void)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = GetDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"Data\\TEXTURE\\water02.jpg",
		&g_pTextureMeshWall);

	g_posMeshWall = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotMeshWall = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_nSplitBesideWall = 3;
	g_nSplitVerticalWall = 5;
	g_fWidthWall = 100.0f;

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * (g_nSplitBesideWall * g_nSplitVerticalWall),
		D3DUSAGE_WRITEONLY,
		{ FVF_VERTEX_3D },
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshWall,
		NULL);

	pDevice->CreateIndexBuffer(sizeof(WORD) * ((g_nSplitVerticalWall * 2 * (g_nSplitBesideWall - 1)) + ((g_nSplitBesideWall - 2) * 2)), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_pIdxBuffMeshWall, NULL);

	VERTEX_3D * pVtx;
	g_pVtxBuffMeshWall->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	for (int nB = 0; nB < g_nSplitBesideWall; nB++)
	{
		for (int nV = 0; nV < g_nSplitVerticalWall; nV++)
		{
			pVtx[(nV + (nB * g_nSplitVerticalWall))].pos = D3DXVECTOR3((-g_fWidthWall * (g_nSplitVerticalWall - 1) / 2) + g_fWidthWall * nV, (g_fWidthWall * (g_nSplitBesideWall - 1) ) + -g_fWidthWall * nB, 0.0f);
		}
	}

	//�@���x�N�g���̐ݒ�
	for (int nCnt = 0; nCnt < (g_nSplitBesideWall * g_nSplitVerticalWall); nCnt++)
	{
		pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	}

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[8].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�J���[�̐ݒ�

	for (int nCnt = 0; nCnt < (g_nSplitBesideWall * g_nSplitVerticalWall); nCnt++)
	{
		pVtx[nCnt].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	}


	g_pVtxBuffMeshWall->Unlock();

	WORD*pIdx; //�C���f�b�N�X���ւ̃|�C���^
			   //�C���f�b�N�X�o�b�t�@�����b�N���A���_�ԍ��f�[�^�ւ̃|�C���^���擾
	g_pIdxBuffMeshWall->Lock(0, 0, (void**)&pIdx, 0);
	int nCnt1;
	int nCnt2;
	int nPlus = 0;

	for (nCnt1 = 0; nCnt1 < g_nSplitBesideWall-1; nCnt1++)
	{
		for (nCnt2 = 0; nCnt2 < g_nSplitVerticalWall; nCnt2++)
		{
			pIdx[(nCnt2 * 2) + (nCnt1 * g_nSplitVerticalWall * 2) + nPlus] = nCnt2 + ((nCnt1 + 1)*g_nSplitVerticalWall);
			pIdx[(nCnt2 * 2) + (nCnt1 * g_nSplitVerticalWall * 2) + 1 + nPlus] = nCnt2 + ((nCnt1)*g_nSplitVerticalWall);
		}
		if (nCnt1 < g_nSplitBesideWall - 2)
		{
			pIdx[(nCnt2 * 2) + (nCnt1 * g_nSplitVerticalWall * 2) + nPlus] = (nCnt2 - 1) + ((nCnt1)*g_nSplitVerticalWall);
			pIdx[(nCnt2 * 2) + (nCnt1 * g_nSplitVerticalWall * 2) + 1 + nPlus] = nCnt2 + ((nCnt1 + 1)*g_nSplitVerticalWall);
			nPlus += 2;
		}

	}

	//���_�ԍ��f�[�^�̐ݒ�
	//pIdx[0] = 3;
	//pIdx[1] = 0;
	//pIdx[2] = 4;
	//pIdx[3] = 1;
	//pIdx[4] = 5;
	//pIdx[5] = 2;
	//pIdx[6] = 2;
	//pIdx[7] = 6;
	//pIdx[8] = 6;
	//pIdx[9] = 3;
	//pIdx[10] = 7;
	//pIdx[11] = 4;
	//pIdx[12] = 8;
	//pIdx[13] = 5;
	g_pIdxBuffMeshWall->Unlock();
}




//�v���C���[�̏I������
void UninitMeshWall(void)
{
	if (g_pTextureMeshWall != NULL)
	{
		g_pTextureMeshWall->Release();
		g_pTextureMeshWall = NULL;
	}
	if (g_pVtxBuffMeshWall != NULL)
	{
		g_pVtxBuffMeshWall->Release();
		g_pVtxBuffMeshWall = NULL;
	}
	if (g_pIdxBuffMeshWall != NULL)
	{
		g_pIdxBuffMeshWall->Release();
		g_pIdxBuffMeshWall = NULL;
	}
}

//�v���C���[�̍X�V����
void UpdateMeshWall(void)
{

}

//�v���C���[�̕`�揈��
void DrawMeshWall(void)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���N�X

								 //���[���h�}�g���N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldMeshWall);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshWall.y, g_rotMeshWall.x, g_rotMeshWall.z);

	D3DXMatrixMultiply(&g_mtxWorldMeshWall, &g_mtxWorldMeshWall, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posMeshWall.x, g_posMeshWall.y, g_posMeshWall.z);

	D3DXMatrixMultiply(&g_mtxWorldMeshWall, &g_mtxWorldMeshWall, &mtxTrans);

	//���[���h�}�g���N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshWall);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMeshWall, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIdxBuffMeshWall);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureMeshWall);


	//�|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, (g_nSplitBesideWall * g_nSplitVerticalWall), 0, (g_nSplitVerticalWall * 2 * (g_nSplitBesideWall - 1) + ((g_nSplitBesideWall - 3) * 2)));

}

bool CollisionWall(D3DXVECTOR3 pos, D3DXVECTOR3 Oldpos)
{
	D3DXVECTOR3 vecMove = pos - Oldpos;
	VERTEX_3D * pVtx;
	g_pVtxBuffMeshWall->Lock(0, 0, (void**)&pVtx, 0);
	D3DXVECTOR3 vecLine = pVtx[0].pos - pVtx[g_nSplitVerticalWall - 1].pos;
	D3DXVECTOR3 vecToPos = pVtx[0].pos - pos;
	g_pIdxBuffMeshWall->Unlock();
	if ((vecLine.z * vecToPos.x) - (vecLine.x * vecToPos.z) > 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}