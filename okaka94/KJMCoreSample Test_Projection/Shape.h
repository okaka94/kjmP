#pragma once
#include "Object.h"

class Shape : public Object3D		// ���ÿ��� Shape�� ������ ���� Object.h ��Ȱ������
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

