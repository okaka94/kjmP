#pragma once
#include "Object.h"

enum UIState {
	UI_NORMAL,
	UI_PUSH,
	UI_HOVER,
	UI_SELECT,
	UI_DIS,
};

class UI :	public Object2D
{
public:
	UIState				m_Current_state = UI_NORMAL;
	std::vector<Rect>	sprite;
	float				timer = 0.0f;
	Vector2D			UI_size;
public:
	bool Frame() override;
	bool Frame_btn();
	bool Set_UI_size(Vector2D size);
	bool Set_pos_size(Vector2D pos);
	//bool Render() override;
	//bool Release() override;
};

