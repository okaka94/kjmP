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

class Matrix3x3 : public float3x3    // 3x3 ����ü ���
{
public:
	Matrix3x3();					// ������ ���� ��ķ� �����
	void Set_I_matrix();			// ������ķ� �� ����
	Matrix3x3 Return_T_matrix();		// ��ġ���(Transpose) ����
	Matrix3x3 Rotation_matrix(float rad);		// Radian ����ŭ ȸ���� ����� ���ϱ����� ���� ��� ���� _ (���� * ���ϵ� ���) = ȸ���� ��ġ
	Matrix3x3 Scale_matrix(float x, float y);	// x,y ����ŭ Rescale�� ����� ���ϱ����� ���� ��� ���� _ (���� * ���ϵ� ���) = Rescale�� ��ġ
	Matrix3x3 Translation_matrix(float x, float y); // x,y����ŭ �̵� ��ȯ�� ����� ���ϱ����� ���� ��� ����
public:
	Matrix3x3 operator* (Matrix3x3& Operand_m);
};


class Matrix : public float4x4    // 4x4 ����ü ���
{
public:
	Matrix();					// ������ ���� ��ķ� �����
	void Set_I_matrix();			// ������ķ� �� ����
	void Set_Translation_matrix(float x, float y, float z);
	Matrix Return_T_matrix();		// ��ġ���(Transpose) ����
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
	Matrix OrthoLH(float w, float h, float n, float f);									// ��ǥ���� ���� �� �ֵ��� ��ĸ� ��ȯ���� (���ϰ��� ���ؾ� ��ȯ�� ����)
	Matrix OrthoOffCenterLH(float l, float r, float b, float t, float n, float f);
	Matrix PerspectiveFovLH(float n, float f, float FOV_Y, float aspect);				// aspect = W / H (��Ⱦ��)


public:
	Matrix operator* (Matrix& Operand_m);
};
