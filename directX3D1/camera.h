#include "main.h"

#ifndef _Camera_H_
#define _Camera_H_

typedef struct
{
	D3DXVECTOR3 posV;	//視点
	D3DXVECTOR3 posR;	//注視点
	D3DXVECTOR3 posVdest;	//視点
	D3DXVECTOR3 posRdest;	//注視点
	D3DXVECTOR3 vecU;	//上方向ベクトル
	D3DXVECTOR3 rot; //向き
	D3DXVECTOR3 rotDest; //向き目標
	D3DXVECTOR3 moveV;
	D3DXVECTOR3 moveR;
	D3DXMATRIX mtxProjection;	//プロジェクションマトリクス
	D3DXMATRIX mtxView;	//ビューマトリクス
}Camera;

//プロトタイプ宣言
void InitCamera();
void UninitCamera();
void UpdateCamera();
void SetCamera();
Camera GetCamera();
void TurnCamera(float rot);
#endif // !_Camera_H_
