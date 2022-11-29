#include "main.h"
#ifndef _Object_H_
#define _Object_H_

typedef struct
{
	D3DXVECTOR3 Startpos;	//�ʒu
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 move;		//�ړ���
	D3DXVECTOR3 rot;		//����
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
	int nIdxShadow;			//�e�̃C���f�b�N�X�ԍ�
	bool bUse;				//�g�p���Ă��邩
	LPDIRECT3DTEXTURE9 pTexture[30];	//�e�N�X�`���ւ̃|�C���^
	LPD3DXMESH pMesh;		//���b�V��(���_���)�ւ̃|�C���^
	LPD3DXBUFFER pBuffMat;	//�}�e���A���ւ̃|�C���^
	D3DXMATERIAL pMatData[80];	//�}�e���A���̃f�[�^
	DWORD dwNumMat;			//�}�e���A���̐�
}Object;

//�v���g�^�C�v�錾
void InitObject();
void UninitObject();
void UpdateObject();
void DrawObject();

#endif // !_Object_H_
