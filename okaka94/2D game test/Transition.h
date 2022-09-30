#pragma once
#include "UI.h"
class Transition :  public Object2D
{
public:
	std::vector<UI*> m_Img;
	bool state = true;
	Vector2D pos = { 0,0 };
	float timer = 0.0f;
public:
	bool Move_pos(int index, Vector2D pos);
	bool Fade_img(int index, float alpha);
	bool Frame() override;
	bool Release() override;
};

