#pragma once
#include <iostream>
#include <math.h>

#define EPSILON		0.001f
#define PI			3.141592f
#define DEGREE(X)	((X)*(180.0f/PI))
#define RADIAN(X)	((X)*(PI/180.0f))


struct Float2 {						// ����ü���·� �ٷ� ����� �ȵ�
	union {			
		struct {
			float x;
			float y;
		};
		float v[2];
	};
};


class Vector2D : public Float2
{
public:
	Vector2D();
	Vector2D(float x,float y);
	Vector2D(const Vector2D& v);			// ���� ������

public:
	Vector2D operator +  (Vector2D& v);		// ������ �����ε�
	Vector2D operator += (Vector2D& v);
	Vector2D operator -  (Vector2D& v);
	Vector2D operator *  (float scala);
	Vector2D operator /  (float scala);
	Vector2D operator *= (float scala);
	bool	 operator == (Vector2D& v);

public:
	float		Get_sqrd_length();
	float		Get_length();
	void		Normalize_vector();
	Vector2D	Ret_norm_vector();
	float		Get_angle(Vector2D& v);		// ������ ���ؼ� ��Ÿ �� ���ϱ�


};

struct Float3 {						// ����ü���·� �ٷ� ����� �ȵ�
	union {
		struct {
			float x;
			float y;
			float z;
		};
		float v[3];
	};
};


class Vector : public Float3
{
public:
	Vector();
	Vector(float x, float y, float z);
	Vector(const Vector& v);			// ���� ������

public:
	Vector	 operator +   (Vector& v);		// ������ �����ε�
	Vector	 operator +=  (Vector& v);
	Vector	 operator -   (Vector& v);
	Vector	 operator *   (float scala);
	Vector	 operator /   (float scala);
	Vector	 operator *=  (float scala);
	bool	 operator ==  (Vector& v);
	bool	 operator <   (Vector& v);
	bool	 operator <=  (Vector& v);
	bool	 operator >   (Vector& v);
	bool	 operator >=  (Vector& v);

public:
	float		Get_sqrd_length();
	float		Get_length();
	void		Normalize_vector();
	Vector		Ret_norm_vector();
	float		Get_angle(Vector& v);		// ������ ���ؼ� ��Ÿ �� ���ϱ�


};

struct Float4 {						// ����ü���·� �ٷ� ����� �ȵ�
	union {
		struct {
			float x;
			float y;
			float z;
			float w;
		};
		float v[4];
	};
};


class Vector4D : public Float4
{
public:
	Vector4D();
	Vector4D(float x, float y, float z,float w);
	Vector4D(const Vector4D& v);			// ���� ������

public:
	Vector4D	 operator +   (Vector4D& v);		// ������ �����ε�
	Vector4D	 operator +=  (Vector4D& v);
	Vector4D	 operator -   (Vector4D& v);
	Vector4D	 operator *   (float scala);
	Vector4D	 operator /   (float scala);
	Vector4D	 operator *=  (float scala);
	bool	 operator ==  (Vector4D& v);
	bool	 operator <   (Vector4D& v);
	bool	 operator <=  (Vector4D& v);
	bool	 operator >   (Vector4D& v);
	bool	 operator >=  (Vector4D& v);

public:
	float		Get_sqrd_length();
	float		Get_length();
	void		Normalize_vector();
	Vector4D		Ret_norm_vector();
	float		Get_angle(Vector4D& v);		// ������ ���ؼ� ��Ÿ �� ���ϱ�


};

