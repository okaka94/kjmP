#pragma once
#include "Base_object.h"


class Object3D : public Base_object
{
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

class Shape_box : public Object3D {
public:
	virtual void CreateVertexList() override;
	virtual void CreateIndexList() override;
	virtual bool Frame() override;
	virtual bool Render() override;

public:
	Shape_box() {};
	virtual ~Shape_box() {};
};

