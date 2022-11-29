#include "model.h"
#include "shadow.h"
#include "input.h"

//�}�N����`
#define MOVE_SPEED (5.0f)

//�O���[�o���ϐ�

LPD3DXMESH g_pMeshModel = NULL; //���b�V��(���_���)�ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatModel = NULL; //�}�e���A���ւ̃|�C���^
DWORD g_dwNumMatModel = 0; //�}�e���A���̐�
D3DXVECTOR3 g_posModel; //�ʒu
D3DXVECTOR3 g_rotModel; //����
D3DXVECTOR3 g_vtxMinModel, g_vtxMaxModel;
D3DXMATRIX g_mtxWorldModel; //���[���h�}�g���N�X
LPDIRECT3DTEXTURE9 g_pTextureModel[8] = {};
int g_nIndexShadow;

void InitModel()
{
	int nNumVtx; //���_��
	DWORD dwSizeFVF; //���_�t�H�[�}�b�g�̃T�C�Y
	BYTE*pVtxBuff; //���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = GetDevice();

	g_posModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_vtxMinModel = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);
	g_vtxMaxModel = D3DXVECTOR3(-1000.0f, -1000.0f, -1000.0f);
	g_nIndexShadow = SetShadow();

	//x�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("Data\\MODEL\\AbandonedBuilding.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatModel,
		NULL,
		&g_dwNumMatModel,
		&g_pMeshModel);

	//���_�����擾
	nNumVtx = g_pMeshModel->GetNumVertices();

	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	dwSizeFVF = D3DXGetFVFVertexSize(g_pMeshModel->GetFVF());

	//���_�o�b�t�@�����b�N
	g_pMeshModel->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;
		if (g_vtxMinModel.x > vtx.x)
		{
			g_vtxMinModel.x = vtx.x;
		}
		if (g_vtxMinModel.y > vtx.y)
		{
			g_vtxMinModel.y = vtx.y;
		}
		if (g_vtxMinModel.z > vtx.z)
		{
			g_vtxMinModel.z = vtx.z;
		}
		if (g_vtxMaxModel.x < vtx.x)
		{
			g_vtxMaxModel.x = vtx.x;
		}
		if (g_vtxMaxModel.y < vtx.y)
		{
			g_vtxMaxModel.y = vtx.y;
		}
		if (g_vtxMaxModel.z < vtx.z)
		{
			g_vtxMaxModel.z = vtx.z;
		}
		
		pVtxBuff += dwSizeFVF;
	}
	//���_�o�b�t�@���A�����b�N
	g_pMeshModel->UnlockVertexBuffer();

	//�e�N�X�`���̓ǂݍ���
	D3DXMATERIAL *pMat; //�}�e���A���f�[�^�ւ̃|�C���^
	pMat = (D3DXMATERIAL*)g_pBuffMatModel->GetBufferPointer();
	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatModel; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{//�e�N�X�`���t�@�C�������݂��鎞
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_pTextureModel[nCntMat]);
		}
	}
}
void UninitModel()
{
	for (int nCntTex = 0; nCntTex < 8; nCntTex++)
	{
		if (g_pTextureModel[nCntTex] != NULL)
		{
			g_pTextureModel[nCntTex]->Release();
			g_pTextureModel[nCntTex] = NULL;
		}
	}
	//���b�V���̔j��
	if(g_pMeshModel != NULL)
	{
		g_pMeshModel->Release();
		g_pMeshModel = NULL;
	}

	//�}�e���A���̔j��
	if (g_pBuffMatModel != NULL)
	{
		g_pBuffMatModel->Release();
		g_pBuffMatModel = NULL;
	}
}
void UpdateModel()
{
	//�ړ�
	/*if (GetKeyboardPress(DIK_UP) == true)
	{
		g_posModel.z += MOVE_SPEED;
	}
	if (GetKeyboardPress(DIK_DOWN) == true)
	{
		g_posModel.z -= MOVE_SPEED;
	}
	if (GetKeyboardPress(DIK_LEFT) == true)
	{
		g_posModel.x -= MOVE_SPEED;
	}
	if (GetKeyboardPress(DIK_RIGHT) == true)
	{
		g_posModel.x += MOVE_SPEED;
	}*/
	//�e�̈ʒu
	SetPositionShadow(g_nIndexShadow, g_posModel);
}
void DrawModel()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice(); //�f�o�C�X�̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���N�X
	D3DMATERIAL9 matDef; //���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat; //�}�e���A���f�[�^�ւ̃|�C���^

	//���[���h�}�g���N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldModel);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotModel.y, g_rotModel.x, g_rotModel.z);
	D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posModel.x, g_posModel.y, g_posModel.z);
	D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxTrans);

	//���[���h�}�g���N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldModel);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_pBuffMatModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatModel; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureModel[nCntMat]);

		//���f��(�p�[�c)�̕`��
		g_pMeshModel->DrawSubset(nCntMat);
	}
	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}
