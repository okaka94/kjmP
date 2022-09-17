#include "Player_object.h"
#include "Input.h"



bool Player_object2D::Frame() {									// NDC 적용 전 화면좌표계 기준으로 위치값 만들고 Set_position에서 NDC로 변환 작업함
	
	Vector2D pos = m_vPos;
	if (Input::GetInstance().GetKey('W')) {
		pos.y += -1.0f * g_fSecPerFrame * m_fSpeed;
	}

	if (Input::GetInstance().GetKey('A')) {
		pos.x += -1.0f * g_fSecPerFrame * m_fSpeed;
	}

	if (Input::GetInstance().GetKey('S')) {
		pos.y += 1.0f * g_fSecPerFrame * m_fSpeed;
	}

	if (Input::GetInstance().GetKey('D')) {
		pos.x += 1.0f * g_fSecPerFrame * m_fSpeed;
	}

	Set_position(pos);
	
	return true;
}