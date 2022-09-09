#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include "Vector.h"

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

	bool operator == (Rect& operand) {							// �Ǽ��� �񱳴� �������� ��� �ʿ�
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

class Collision
{
public:
	static Collision_type Cmp_rect(Rect& a, Rect& b);			// static Ÿ������ �ϴ� ����? ��������ȭ�ؼ� ����ϱ����� (�ȱ׷��� �ν��Ͻ� �����ؾ���)
	static bool Is_subset(Rect& a, Rect& b);
	static bool Cmp_circle(Circle& a, Circle& b);
};

