#pragma once
#include "Collision.h"


class Object {
public:
	Vector2D	direction;
	Rect		rect;
	Circle		circle;													// �簢���� �������� ����
	
public:
	float		mass;
	float		speed;
	float		friction;
	Vector2D	force;
	Vector2D	acc;
	Vector2D	velocity;


public:
	void Set_circle(float x, float y, float w, float h);			// x, y �� ���ʿ� cx,cy �Ѱ��� (( rect �������  -> circle ������ ���� ))
	void Set_position(float x, float y, float w, float h);
	virtual void Frame(float delta_time);
	virtual void Add_force(Vector2D force);

public:
	Object();
};