#pragma once
#include "Collision.h"

class Quaternion : public XMFLOAT4
{
public:
	Quaternion();
	Quaternion(float x, float y, float z, float w);
	Quaternion(Vector v, float s);
	Quaternion(const Quaternion& v);			// 복사 생성자

public:
	Quaternion	 operator +   (Quaternion& v);		// 연산자 오버로딩
	Quaternion	 operator +=  (Quaternion& v);
	Quaternion	 operator -   (Quaternion& v);
	Quaternion	 operator *   (Quaternion& v);
	Quaternion	 operator *   (float scala);
	Quaternion	 operator /   (float scala);
	Quaternion	 operator *=  (float scala);

public:
	void		Set_identity();
	void		Set_conjugate();
	Quaternion  Ret_conjugate();
	void		Set_inverse();
	float		Get_sqrd_length();
	float		Get_length();
	void		Set_normalized();
	Quaternion  Ret_rotated_quat(Vector axis, float angle);
	Matrix		RotationQ_to_Mat();
	void		Normalize_axis();
	void		Set_Slerp(const Quaternion& q1, const Quaternion& q2, float t);
};

