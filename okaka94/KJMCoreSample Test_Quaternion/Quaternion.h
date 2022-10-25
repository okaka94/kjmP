#pragma once
#include "Collision.h"

class Quaternion : public Float4
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
	void		Set_inverse();
	float		Get_sqrd_length();
	float		Get_length();

};

