#include "Player_object.h"
#include "Input.h"



bool Player_object2D::Frame() {									// NDC 적용 전 화면좌표계 기준으로 위치값 만들고 Set_position에서 NDC로 변환 작업함
	
	
	if (Input::GetInstance().GetKey('W')) {
		m_vPos.y += -1.0f * g_fSecPerFrame * m_fSpeed;
	}

	if (Input::GetInstance().GetKey('A')) {
		m_vPos.x += -1.0f * g_fSecPerFrame * m_fSpeed;
	}

	if (Input::GetInstance().GetKey('S')) {
		m_vPos.y += 1.0f * g_fSecPerFrame * m_fSpeed;
	}

	if (Input::GetInstance().GetKey('D')) {
		m_vPos.x += 1.0f * g_fSecPerFrame * m_fSpeed;
	}
	//Set_position(pos);

	m_VertexList[0].c = { 1,1,1,cosf(g_fGameTimer) * 0.5f+0.5f };
	m_VertexList[1].c = { 1,1,1,cosf(g_fGameTimer) * 0.5f + 0.5f };
	m_VertexList[2].c = { 1,1,1,cosf(g_fGameTimer) * 0.5f + 0.5f };
	m_VertexList[3].c = { 1,1,1,cosf(g_fGameTimer) * 0.5f + 0.5f };

	ScreenToNDC();			// 화면 좌표계 -> NDC 좌표계

	UpdateVertextBuffer();
	
	return true;
}