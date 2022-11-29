#include "Character.h"
#include "shadow.h"
#include "input.h"
#include "camera.h"
#include "bullet.h"

//�}�N����`
#define MOVE_SPEED (5.0f)

#define SPEED_DOWN (0.9f)

//�O���[�o���ϐ�

LPD3DXMESH g_pMeshCharacter = NULL; //���b�V��(���_���)�ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatCharacter = NULL; //�}�e���A���ւ̃|�C���^
DWORD g_dwNumMatCharacter = 0; //�}�e���A���̐�
D3DXVECTOR3 g_posCharacter; //�ʒu
D3DXVECTOR3 g_rotCharacter; //����
D3DXMATRIX g_mtxWorldCharacter; //���[���h�}�g���N�X
LPDIRECT3DTEXTURE9 g_pTextureCharacter[8] = {};


characte g_chara;

void InitCharacter()
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = GetDevice();

	g_chara.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_chara.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_chara.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_chara.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_chara.InputCount = 0;

	g_chara.nIndexShadow = SetShadow();

	//x�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("Data\\MODEL\\13_head.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatCharacter,
		NULL,
		&g_dwNumMatCharacter,
		&g_pMeshCharacter);

	//�e�N�X�`���̓ǂݍ���
	D3DXMATERIAL *pMat; //�}�e���A���f�[�^�ւ̃|�C���^
	pMat = (D3DXMATERIAL*)g_pBuffMatCharacter->GetBufferPointer();
	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatCharacter; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{//�e�N�X�`���t�@�C�������݂��鎞
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_pTextureCharacter[nCntMat]);
		}
	}
}
void UninitCharacter()
{
	for (int nCntTex = 0; nCntTex < 8; nCntTex++)
	{
		if (g_pTextureCharacter[nCntTex] != NULL)
		{
			g_pTextureCharacter[nCntTex]->Release();
			g_pTextureCharacter[nCntTex] = NULL;
		}
	}
	//���b�V���̔j��
	if (g_pMeshCharacter != NULL)
	{
		g_pMeshCharacter->Release();
		g_pMeshCharacter = NULL;
	}

	//�}�e���A���̔j��
	if (g_pBuffMatCharacter != NULL)
	{
		g_pBuffMatCharacter->Release();
		g_pBuffMatCharacter = NULL;
	}
}
void UpdateCharacter()
{
	Camera camera = GetCamera();


	//�ړ�
	if (GetKeyboardPress(DIK_UP) == true)
	{
		g_chara.move.x += sinf(camera.rot.y)*MOVE_SPEED;
		g_chara.move.z += cosf(camera.rot.y)*MOVE_SPEED;
	}
	if (GetKeyboardPress(DIK_DOWN) == true)
	{
		g_chara.move.x -= sinf(camera.rot.y)*MOVE_SPEED;
		g_chara.move.z -= cosf(camera.rot.y)*MOVE_SPEED;
	}
	if (GetKeyboardPress(DIK_LEFT) == true)
	{
		g_chara.move.z -= sinf(-camera.rot.y)*MOVE_SPEED;
		g_chara.move.x -= cosf(-camera.rot.y)*MOVE_SPEED;
	}
	if (GetKeyboardPress(DIK_RIGHT) == true)
	{
		g_chara.move.z += sinf(-camera.rot.y)*MOVE_SPEED;
		g_chara.move.x += cosf(-camera.rot.y)*MOVE_SPEED;
	}
	if (GetKeyboardTrigger(DIK_SPACE) == true)
	{
		SetBullet(D3DXVECTOR3(g_chara.pos.x, 30.0f, g_chara.pos.z), D3DXVECTOR3(0.0f,0.0f,10.0f),g_chara.rot,20,60);
	}
	

	if (g_chara.move != D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	{
		g_chara.rotDest.y = (fmodf(((float)atan2f(g_chara.move.x, g_chara.move.z) / D3DX_PI) + 1, 2) - 1.0f) * D3DX_PI;
		g_chara.InputCount = 0;
	}
	else
	{
		g_chara.InputCount++;
	}
	
	if (g_chara.rot != g_chara.rotDest)
	{
		g_chara.rot += (g_chara.rotDest - g_chara.rot) / 10;
	}

	if (g_chara.InputCount >= 120)
	{
		TurnCamera(g_chara.rot.y);
		g_chara.InputCount = 0;
	}

	g_chara.pos += g_chara.move;
	g_chara.move.x += (0.0f - g_chara.move.x)*SPEED_DOWN;
	g_chara.move.y += (0.0f - g_chara.move.y)*SPEED_DOWN;
	g_chara.move.z += (0.0f - g_chara.move.z)*SPEED_DOWN;
	
	//�e�̈ʒu
	SetPositionShadow(g_chara.nIndexShadow, g_chara.pos);
}
void DrawCharacter()
{
	
	LPDIRECT3DDEVICE9 pDevice = GetDevice(); //�f�o�C�X�̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���N�X
	D3DMATERIAL9 matDef; //���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat; //�}�e���A���f�[�^�ւ̃|�C���^

						//���[���h�}�g���N�X�̏�����
	D3DXMatrixIdentity(&g_chara.mtx);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_chara.rot.y, g_chara.rot.x, g_chara.rot.z);
	D3DXMatrixMultiply(&g_chara.mtx, &g_chara.mtx, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_chara.pos.x, g_chara.pos.y, g_chara.pos.z);
	D3DXMatrixMultiply(&g_chara.mtx, &g_chara.mtx, &mtxTrans);

	//���[���h�}�g���N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_chara.mtx);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_pBuffMatCharacter->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatCharacter; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureCharacter[nCntMat]);

		//���f��(�p�[�c)�̕`��
		g_pMeshCharacter->DrawSubset(nCntMat);
	}
	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

characte Getcharacte()
{
	return g_chara;
}