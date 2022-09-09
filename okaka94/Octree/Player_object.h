#pragma once
#include "Object.h"
class Player_object3D :  public Object3D
{
public:
	void Frame(float delta_time) override;
	virtual void Set_default() override;
	void Render() override;
	//Player_object3D();
	//~Player_object3D();
};

class Player_object2D : public Object2D
{
public:
	void Frame(float delta_time) override;
	void Render() override;
	virtual void Set_default() override;
	//Player_object2D();
	//~Player_object2D();
};
