#include "Object.h"
#include "shadow.h"
#include "input.h"

//�}�N����`
#define MOVE_SPEED (5.0f)
#define MAX_OBJECT (24)

//�O���[�o���ϐ�

LPD3DXMESH g_pMeshObject = NULL; //���b�V��(���_���)�ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatObject = NULL; //�}�e���A���ւ̃|�C���^
DWORD g_dwNumMatObject = 0; //�}�e���A���̐�
D3DXVECTOR3 g_posObject; //�ʒu
D3DXVECTOR3 g_rotObject; //����
D3DXVECTOR3 g_vtxMinObject, g_vtxMaxObject;
D3DXMATRIX g_mtxWorldObject; //���[���h�}�g���N�X
LPDIRECT3DTEXTURE9 g_pTextureObject[8] = {};
int g_nIndexShadow;

Object g_aObject[MAX_OBJECT];

void InitObject()
{
	int nNumVtx; //���_��
	DWORD dwSizeFVF; //���_�t�H�[�}�b�g�̃T�C�Y
	BYTE*pVtxBuff; //���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = GetDevice();

	g_posObject = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotObject = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_vtxMinObject = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);
	g_vtxMaxObject = D3DXVECTOR3(-1000.0f, -1000.0f, -1000.0f);
	g_nIndexShadow = SetShadow();

	//x�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("Data\\Object\\AbandonedBuilding.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatObject,
		NULL,
		&g_dwNumMatObject,
		&g_pMeshObject);

	//���_�����擾
	nNumVtx = g_pMeshObject->GetNumVertices();

	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	dwSizeFVF = D3DXGetFVFVertexSize(g_pMeshObject->GetFVF());

	//���_�o�b�t�@�����b�N
	g_pMeshObject->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;
		if (g_vtxMinObject.x > vtx.x)
		{
			g_vtxMinObject.x = vtx.x;
		}
		if (g_vtxMinObject.y > vtx.y)
		{
			g_vtxMinObject.y = vtx.y;
		}
		if (g_vtxMinObject.z > vtx.z)
		{
			g_vtxMinObject.z = vtx.z;
		}
		if (g_vtxMaxObject.x < vtx.x)
		{
			g_vtxMaxObject.x = vtx.x;
		}
		if (g_vtxMaxObject.y < vtx.y)
		{
			g_vtxMaxObject.y = vtx.y;
		}
		if (g_vtxMaxObject.z < vtx.z)
		{
			g_vtxMaxObject.z = vtx.z;
		}

		pVtxBuff += dwSizeFVF;
	}
	//���_�o�b�t�@���A�����b�N
	g_pMeshObject->UnlockVertexBuffer();

	//�e�N�X�`���̓ǂݍ���
	D3DXMATERIAL *pMat; //�}�e���A���f�[�^�ւ̃|�C���^
	pMat = (D3DXMATERIAL*)g_pBuffMatObject->GetBufferPointer();
	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatObject; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{//�e�N�X�`���t�@�C�������݂��鎞
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_pTextureObject[nCntMat]);
		}
	}
}
void UninitObject()
{
	for (int nCntTex = 0; nCntTex < 8; nCntTex++)
	{
		if (g_pTextureObject[nCntTex] != NULL)
		{
			g_pTextureObject[nCntTex]->Release();
			g_pTextureObject[nCntTex] = NULL;
		}
	}
	//���b�V���̔j��
	if (g_pMeshObject != NULL)
	{
		g_pMeshObject->Release();
		g_pMeshObject = NULL;
	}

	//�}�e���A���̔j��
	if (g_pBuffMatObject != NULL)
	{
		g_pBuffMatObject->Release();
		g_pBuffMatObject = NULL;
	}
}
void UpdateObject()
{
	//�ړ�
	/*if (GetKeyboardPress(DIK_UP) == true)
	{
	g_posObject.z += MOVE_SPEED;
	}
	if (GetKeyboardPress(DIK_DOWN) == true)
	{
	g_posObject.z -= MOVE_SPEED;
	}
	if (GetKeyboardPress(DIK_LEFT) == true)
	{
	g_posObject.x -= MOVE_SPEED;
	}
	if (GetKeyboardPress(DIK_RIGHT) == true)
	{
	g_posObject.x += MOVE_SPEED;
	}*/
	//�e�̈ʒu
	SetPositionShadow(g_nIndexShadow, g_posObject);
}
void DrawObject()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice(); //�f�o�C�X�̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���N�X
	D3DMATERIAL9 matDef; //���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat; //�}�e���A���f�[�^�ւ̃|�C���^

						//���[���h�}�g���N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldObject);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotObject.y, g_rotObject.x, g_rotObject.z);
	D3DXMatrixMultiply(&g_mtxWorldObject, &g_mtxWorldObject, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posObject.x, g_posObject.y, g_posObject.z);
	D3DXMatrixMultiply(&g_mtxWorldObject, &g_mtxWorldObject, &mtxTrans);

	//���[���h�}�g���N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldObject);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_pBuffMatObject->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatObject; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureObject[nCntMat]);

		//���f��(�p�[�c)�̕`��
		g_pMeshObject->DrawSubset(nCntMat);
	}
	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}
