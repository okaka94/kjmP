#pragma once
#include "Base_object.h"

class Object3D : public Base_object
{
public:
	void Set_sphere(Box box);			// x, y �� ���ʿ� cx,cy �Ѱ��� (( rect �������  -> circle ������ ���� ))
	void Set_sphere(Vector v_center, float r);
	void Set_position(Vector v_pos, Vector v_size);
	virtual void Frame(float delta_time) override;
	virtual void Add_force(Vector force);
	virtual void Set_default();
	virtual bool Render();
	virtual bool Init();
	

public:
	Object3D();
	virtual ~Object3D();
};



class Object2D : public Base_object
{
public:
	void Set_circle(float x, float y, float w, float h);			// x, y �� ���ʿ� cx,cy �Ѱ��� (( rect �������  -> circle ������ ���� ))
	void Set_position(float x, float y, float w, float h);
	virtual void Frame(float delta_time) override;
	virtual void Add_force(Vector2D force);
	virtual void Set_default();
	virtual bool Render();
	virtual bool Init() override;
	

public:
	Object2D();
	virtual ~Object2D();
};
