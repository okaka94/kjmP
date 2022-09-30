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
	
public:
	bool Frame() override;
	bool Frame_btn();
	//bool Render() override;
	//bool Release() override;
};

