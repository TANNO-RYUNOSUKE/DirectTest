#include "main.h"
#include "MeshField.h"

//�O���[�o���ϐ�

LPDIRECT3DTEXTURE9 g_pTextureMeshField = NULL; //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshField = NULL; //���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshField = NULL; //�C���f�b�N�X�o�b�t�@�ւ̃|�C���^

D3DXVECTOR3 g_posMeshField;
D3DXVECTOR3 g_rotMeshField;
D3DXMATRIX g_mtxWorldMeshField;
int g_nSplitBeside;
int g_nSplitVertical;
float g_fWidth;

void InitMeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = GetDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"Data\\TEXTURE\\water02.jpg",
		&g_pTextureMeshField);

	g_posMeshField = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotMeshField = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_nSplitBeside = 3;
	g_nSplitVertical = 3;
	g_fWidth = 300.0f;

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * (g_nSplitBeside * g_nSplitVertical),
		D3DUSAGE_WRITEONLY,
		{ FVF_VERTEX_3D },
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshField,
		NULL);

	pDevice->CreateIndexBuffer(sizeof(WORD) * ((g_nSplitVertical * 2 * (g_nSplitBeside-1)) + ((g_nSplitBeside - 2) * 2)), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_pIdxBuffMeshField,NULL);

	VERTEX_3D * pVtx;
	g_pVtxBuffMeshField->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	for (int nB = 0; nB < g_nSplitBeside; nB++)
	{
		for (int nV = 0; nV < g_nSplitVertical; nV++)
		{
			pVtx[(nV + (nB * g_nSplitVertical))].pos = D3DXVECTOR3((-g_fWidth * (g_nSplitVertical-1) /2) + g_fWidth * nV, 0.0f, (g_fWidth * (g_nSplitBeside - 1 )/ 2) + -g_fWidth * nB);
		}
	}

	//�@���x�N�g���̐ݒ�
	for (int nCnt = 0; nCnt < (g_nSplitBeside * g_nSplitVertical); nCnt++)
	{
		pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	}
	
	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[8].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�J���[�̐ݒ�

	for (int nCnt = 0; nCnt < (g_nSplitBeside * g_nSplitVertical); nCnt++)
	{
		pVtx[nCnt].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	}
	

	g_pVtxBuffMeshField->Unlock();

	WORD*pIdx; //�C���f�b�N�X���ւ̃|�C���^
	//�C���f�b�N�X�o�b�t�@�����b�N���A���_�ԍ��f�[�^�ւ̃|�C���^���擾
	g_pIdxBuffMeshField->Lock(0, 0, (void**)&pIdx, 0);
	int nCnt1;
	int nCnt2;
	int nPlus = 0;

	for ( nCnt1 = 0; nCnt1 < g_nSplitBeside-1; nCnt1++)
	{
		for ( nCnt2 = 0; nCnt2 < g_nSplitVertical; nCnt2++)
		{
			pIdx[(nCnt2 * 2) + (nCnt1 * g_nSplitVertical*2)+ nPlus] = nCnt2 + ((nCnt1 + 1)*g_nSplitVertical);
			pIdx[(nCnt2 * 2) + (nCnt1 * g_nSplitVertical*2) + 1 + nPlus] = nCnt2 + ((nCnt1)*g_nSplitVertical);
		}
		if (nCnt1 < g_nSplitBeside-2)
		{
			pIdx[(nCnt2 * 2) + (nCnt1 * g_nSplitVertical*2) + nPlus] = (nCnt2 - 1) + ((nCnt1)*g_nSplitVertical);
			pIdx[(nCnt2 * 2) + (nCnt1 * g_nSplitVertical*2) + 1 + nPlus] = nCnt2 + ((nCnt1 + 1)*g_nSplitVertical);
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
	g_pIdxBuffMeshField->Unlock();
}




//�v���C���[�̏I������
void UninitMeshField(void)
{
	if (g_pTextureMeshField != NULL)
	{
		g_pTextureMeshField->Release();
		g_pTextureMeshField = NULL;
	}
	if (g_pVtxBuffMeshField != NULL)
	{
		g_pVtxBuffMeshField->Release();
		g_pVtxBuffMeshField = NULL;
	}
	if (g_pIdxBuffMeshField != NULL)
	{
		g_pIdxBuffMeshField->Release();
		g_pIdxBuffMeshField = NULL;
	}
}

//�v���C���[�̍X�V����
void UpdateMeshField(void)
{

}

//�v���C���[�̕`�揈��
void DrawMeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���N�X

								 //���[���h�}�g���N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldMeshField);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshField.y, g_rotMeshField.x, g_rotMeshField.z);

	D3DXMatrixMultiply(&g_mtxWorldMeshField, &g_mtxWorldMeshField, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posMeshField.x, g_posMeshField.y, g_posMeshField.z);

	D3DXMatrixMultiply(&g_mtxWorldMeshField, &g_mtxWorldMeshField, &mtxTrans);

	//���[���h�}�g���N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshField);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMeshField, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIdxBuffMeshField);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureMeshField);

	
		//�|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, (g_nSplitBeside * g_nSplitVertical), 0, (g_nSplitVertical * 2 * (g_nSplitBeside - 1) + ((g_nSplitBeside - 3) * 2)));

}