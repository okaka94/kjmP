#pragma once
#include "Base_object.h"


class Object3D : public Base_object
{
public:
	W_STR  m_obj_name;
	Vector m_pos;
	Vector m_LookV;
	Vector m_UpV;
	Vector m_RightV;
public:
	virtual void Set_axis() { return; }
public:
	Object3D() {};
	virtual ~Object3D() {};
	
};

class Shape : public Object3D		
{
public:
	Shape() {};
	virtual ~Shape() {};
};

class Shape_box : public Shape {
public:
	Shape*		 m_Axis = nullptr;
public:
	virtual void CreateVertexList() override;
	virtual void CreateIndexList() override;
	virtual bool Frame() override;
	virtual bool Render() override;
	virtual bool Release() override;
	virtual void Set_axis() override;
	virtual void SetMatrix(Matrix* World, Matrix* View, Matrix* Proj) override;


public:
	Shape_box() {};
	virtual ~Shape_box() {};
};


class Shape_line : public Shape
{
public:
	virtual void		CreateVertexList() override;
	virtual void		CreateIndexList() override;
	virtual bool		Frame() override;
	virtual bool		Render() override;
public:
	Shape_line() {};
	virtual ~Shape_line() {};
};


class Shape_axis : public Shape_line
{
public:
	virtual void		CreateVertexList() override;
	virtual void		CreateIndexList() override;
public:
	Shape_axis() {};
	virtual ~Shape_axis() {};
};
