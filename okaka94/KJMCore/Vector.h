#pragma once

#include <iostream>
#include <math.h>
#include <windows.h>

#define EPSILON		0.001f
#define PI			3.141592f
#define DEGREE(X)	((X)*(180.0f/PI))
#define RADIAN(X)	((X)*(PI/180.0f))

/// //////////////////////////// DX Math Lib
#include <d3d11_1.h> 
//#include <d3dx11.h> 
#if !defined(__d3d11_h__) && !defined(__d3d11_x_h__) && !defined(__d3d12_h__) && !defined(__d3d12_x_h__)
#error include d3d11.h or d3d12.h before including TMath.h
#endif

#if !defined(_XBOX_ONE) || !defined(_TITLE)
//#include <dxgi1_2.h>
#endif

#include <functional>
#include <assert.h>
#include <memory.h>

#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXCollision.h>

#ifndef XM_CONSTEXPR
#define XM_CONSTEXPR
#endif

using namespace DirectX;
using namespace DirectX::PackedVector;

class Matrix;

struct Float2 {						// 공용체상태로 바로 상속이 안됨
	union {			
		struct {
			float x;
			float y;
		};
		float v[2];
	};
};


class Vector2D : public XMFLOAT2
{
public:
	Vector2D();
	Vector2D(float x,float y);
	Vector2D(const Vector2D& v);			// 복사 생성자

public:
	Vector2D operator +  (Vector2D& v);		// 연산자 오버로딩
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
	float		Get_angle(Vector2D& v);		// 내적을 구해서 세타 값 구하기


};

struct Float3 {						// 공용체상태로 바로 상속이 안됨
	union {
		struct {
			float x;
			float y;
			float z;
		};
		float v[3];
	};
};


class Vector : public XMFLOAT3
{
public:
	Vector();
	Vector(float x, float y, float z);
	Vector(const Vector& v);			// 복사 생성자

public:
	Vector	 operator +   (Vector& v);		// 연산자 오버로딩
	Vector	 operator +=  (Vector& v);
	Vector	 operator -   (Vector& v);
	Vector	 operator *   (float scala);
	Vector	 operator /   (float scala);
	Vector	 operator *=  (float scala);
	Vector	 operator *   (Matrix& Operand_m);
	float	 operator |   (Vector& v);		// 내적
	Vector	 operator ^   (Vector& v);		// 외적
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
	float		Get_angle(Vector& v);		// 내적을 구해서 세타 값 구하기
	void		Set_Lerp(const Vector& v1, const Vector& v2, float t);

};

struct Float4 {						// 공용체상태로 바로 상속이 안됨
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


class Vector4D : public XMFLOAT4
{
public:
	Vector4D();
	Vector4D(float x, float y, float z,float w);
	Vector4D(const Vector4D& v);			// 복사 생성자

public:
	Vector4D	 operator +   (Vector4D& v);		// 연산자 오버로딩
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
	float		Get_angle(Vector4D& v);		// 내적을 구해서 세타 값 구하기


};

