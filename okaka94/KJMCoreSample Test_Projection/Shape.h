#pragma once
#include "Object.h"

class Shape : public Object3D		// 샘플에는 Shape에 있지만 기존 Object.h 재활용했음
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

