#ifndef _MeshWall_H_
#define _MeshWall_H_
#include "main.h"
//�v���g�^�C�v�錾
void InitMeshWall();
void UninitMeshWall();
void UpdateMeshWall();
void DrawMeshWall();
bool CollisionWall(D3DXVECTOR3 pos ,D3DXVECTOR3 Oldpos);

#endif // !_MeshWall_H_

