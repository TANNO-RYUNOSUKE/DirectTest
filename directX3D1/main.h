#ifndef  _MAIN_H_
#define _MAIN_H_


//==================
//���C���w�b�_�[
//==================
#include<Windows.h>
#include"d3dx9.h" //�`�揈���ɕK�v

#define DIRECTINPUT_VERSION (0x0800)
#include "dinput.h"
#include "xaudio2.h"

//���C�u�����Ƀ����N
#pragma comment(lib,"d3d9.lib")//�`�揈���ɕK�v
#pragma comment(lib,"d3dx9.lib")//{d3d9.lib}�̊g�����C�u����
#pragma comment(lib,"dxguid.lib")//DirectX�R���|�[�l���g�ɕK�v
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"xinput.lib") //�W���C�p�b�h�p
#include "Xinput.h" //�W���C�p�b�h�p�w�b�_

//�}�N����`
#define SCREEN_WIDTH (1280)//�E�B���h�E��
#define SCREEN_HEIGHT (720)//����
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

typedef enum
{
	MODE_TITLE = 0,
	MODE_GAME,
	MODE_RESULT,
	MODE_Tutorial,
	MODE_MAX
}MODE;

//���_���̍\���̂��`(2D)
typedef struct
{
	D3DXVECTOR3 pos; //���_���W
	float rhw; //���W�ϊ��p�W��(1.0f)
	D3DCOLOR col; //���_�J���[
	D3DXVECTOR2 tex; //�e�N�X�`�����W
}VERTEX_2D;

//���_���̍\���̂��`(3D)
typedef struct
{
	D3DXVECTOR3 pos; //���_���W
	D3DXVECTOR3 nor; //�@���x�N�g��
	D3DCOLOR col; //���_�J���[
	D3DXVECTOR2 tex; //�e�N�X�`�����W
}VERTEX_3D;

LPD3DXFONT GetFont();

LPDIRECT3DDEVICE9 GetDevice(void);
void SetMode(MODE mode);
MODE GetMode(void);

#endif // ! _MAIN_H_