#include "main.h"

#ifndef _Camera_H_
#define _Camera_H_

typedef struct
{
	D3DXVECTOR3 posV;	//���_
	D3DXVECTOR3 posR;	//�����_
	D3DXVECTOR3 posVdest;	//���_
	D3DXVECTOR3 posRdest;	//�����_
	D3DXVECTOR3 vecU;	//������x�N�g��
	D3DXVECTOR3 rot; //����
	D3DXVECTOR3 rotDest; //�����ڕW
	D3DXVECTOR3 moveV;
	D3DXVECTOR3 moveR;
	D3DXMATRIX mtxProjection;	//�v���W�F�N�V�����}�g���N�X
	D3DXMATRIX mtxView;	//�r���[�}�g���N�X
}Camera;

//�v���g�^�C�v�錾
void InitCamera();
void UninitCamera();
void UpdateCamera();
void SetCamera();
Camera GetCamera();
void TurnCamera(float rot);
#endif // !_Camera_H_
