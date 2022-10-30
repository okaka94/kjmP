#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include "Vector.h"
#include "Matrix.h"

enum Collision_type {
	RECT_OUT = 0,
	RECT_IN,
	RECT_OVERLAP
};

struct Circle {

	float cx;
	float cy;
	float r;

	Circle() {}

	Circle(float cx, float cy, float r) {
		this->cx = cx;
		this->cy = cy;
		this->r = r;
	}

};

struct Rect {
	
	float x;
	float y;
	float w;
	float h;

	float nx;  // x+w
	float ny;  // y+h
	float cx;
	float cy;

	bool operator == (Rect& operand) {							// 실수의 비교는 오차범위 고려 필요
		if (fabs(x - operand.x) < 0.001f) {

			if (fabs(y - operand.y) < 0.001f) {

				if (fabs(w - operand.w) < 0.001f) {

					if (fabs(h - operand.h) < 0.001f)
						
						return true;

				}
			}
		}
		return false;
	}
	Rect() {};

	Rect(float x, float y, float w, float h) {
		Set_rect(x, y, w, h);
	}
	void Set_rect(float x, float y, float w, float h) {
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;

		nx = x + w;
		ny = y + h;
		cx = (x + nx) / 2.0f;
		cy = (y + ny) / 2.0f;


	}
	

};

/// ///////////////////////////////////

struct Sphere {

	Vector v_center;
	float  r;

	Sphere() {}

	Sphere(Vector v_center, float r) {
		this->v_center = v_center;
		this->r = r;
	}

};

struct AABB
{
	Vector v_min;
	Vector v_max;

	AABB() {}

	AABB(Vector v_min, Vector v_max) {
		this->v_min = v_min;
		this->v_max = v_max;
	}
};
struct OBB
{
	Vector v_center;
	Vector axis[3];
	float  extent[3];
};


struct Box {

	Vector vPos[8];

	//// AABB
	Vector v_min;
	Vector v_max;  // min + size
	Vector v_size;

	//// OBB	
	Vector v_center;
	Vector axis[3];
	float  extent[3];

	bool operator == (Box& operand) {							// 실수의 비교는 오차범위 고려 필요
		if (v_min == operand.v_min){							// 벡터클래스 연산자 오버로딩되어 있음 (오차범위 고려하여)
				if (v_size == operand.v_size) {
						return true;
				}
		}
		return false;
	}

	Box() {};

	Box(Vector v_min, Vector v_size) {
		Set_box(v_min, v_size);
	}
	void Set_box(Vector v_min, Vector v_size){
		
		this->v_min = v_min;
		this->v_size = v_size;
		v_max = v_min + v_size;
		v_center = (v_min + v_max) / 2.0f;

	}


};

class Collision
{
public:
	static Collision_type Cmp_rect(Rect& a, Rect& b);			// static 타입으로 하는 이유? 전역변수화해서 사용하기위해 (안그러면 인스턴스 생성해야함)
	static bool Is_subset(Rect& a, Rect& b);
	static bool Cmp_circle(Circle& a, Circle& b);

public:
	static Collision_type Cmp_box(Box& a, Box& b);
	static bool Is_subset(Box& a, Box& b);
	static bool Cmp_sphere(Sphere& a, Sphere& b);
};

