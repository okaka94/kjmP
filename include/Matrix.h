#pragma once
#include "Vector.h"

struct float3x3 {
	union {
		struct {
			float _11, _12, _13;
			float _21, _22, _23;
			float _31, _32, _33;
		};
		float m[3][3];
	};
};

struct float4x4 {
	union {
		struct {
			float _11, _12, _13, _14;
			float _21, _22, _23, _24;
			float _31, _32, _33, _34;
			float _41, _42, _43, _44;
		};
		float m[4][4];
	};
};

class Matrix3x3 : public float3x3    // 3x3 구조체 상속
{
public:
	Matrix3x3();					// 생성시 단위 행렬로 만들기
	void Set_I_matrix();			// 단위행렬로 값 설정
	Matrix3x3 Return_T_matrix();		// 전치행렬(Transpose) 리턴
	Matrix3x3 Rotation_matrix(float rad);		// Radian 값만큼 회전된 행렬을 구하기위한 계산식 행렬 리턴 _ (정점 * 리턴된 행렬) = 회전된 위치
	Matrix3x3 Scale_matrix(float x, float y);	// x,y 값만큼 Rescale된 행렬을 구하기위한 계산식 행렬 리턴 _ (정점 * 리턴된 행렬) = Rescale된 위치
	Matrix3x3 Translation_matrix(float x, float y); // x,y값만큼 이동 변환된 행렬을 구하기위한 계산식 행렬 리턴
public:
	Matrix3x3 operator* (Matrix3x3& Operand_m);
};


class Matrix : public float4x4    // 4x4 구조체 상속
{
public:
	Matrix();					// 생성시 단위 행렬로 만들기
	void Set_I_matrix();			// 단위행렬로 값 설정
	void Set_Translation_matrix(float x, float y, float z);
	Matrix Return_T_matrix();		// 전치행렬(Transpose) 리턴
	// S R T
	Matrix Rotation_X_matrix(float rad);
	Matrix Rotation_Y_matrix(float rad);
	Matrix Rotation_Z_matrix(float rad);
	Matrix Scale_matrix(float x, float y, float z);
	Matrix Translation_matrix(float x, float y, float z); 
	// Viewing Matrix
	Matrix View_LookAt(Vector& Eye, Vector& At, Vector& vir_Up);
	void Object_LookAt(Vector& Pos, Vector& At, Vector& vir_Up);
	// Projection Matrix 
	Matrix OrthoLH(float w, float h, float n, float f);									// 좌표값에 곱할 수 있도록 행렬만 반환해줌 (리턴값과 곱해야 변환값 나옴)
	Matrix OrthoOffCenterLH(float l, float r, float b, float t, float n, float f);
	Matrix PerspectiveFovLH(float n, float f, float FOV_Y, float aspect);				// aspect = W / H (종횡비)


public:
	Matrix operator* (Matrix& Operand_m);
};
