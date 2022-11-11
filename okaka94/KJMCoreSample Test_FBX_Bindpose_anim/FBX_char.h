#pragma once
#include "FBX_loader.h"

struct Action_table {
	UINT			Start_frame;
	UINT			End_frame;
	float			TickPerFrame;		// 프레임당 틱 (보통 160)
	float			Frame_speed;		// 초당 프레임 (보통 30fps)
	bool			Loop_state;
	Action_table() {
		Loop_state = false;
	}
};


class FBX_char
{
public:
	FBX_loader*								m_FBX_loader = nullptr;
	Anim_scene								m_Anim_scene;
	std::map<std::wstring, Action_table>	m_Action_map;


};

