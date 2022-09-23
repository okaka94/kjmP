#include "Player_object.h"
#include "Input.h"



bool Player_object2D::Frame() {									// NDC ���� �� ȭ����ǥ�� �������� ��ġ�� ����� Set_position���� NDC�� ��ȯ �۾���
	
	
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

	ScreenToNDC();			// ȭ�� ��ǥ�� -> NDC ��ǥ��

	UpdateVertextBuffer();
	
	return true;
}