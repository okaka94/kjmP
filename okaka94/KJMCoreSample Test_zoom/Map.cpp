#include "Map.h"

bool Map::Frame() {
	Vector2D Position = m_vPos;


	Set_position(Position, m_vCamPos);

	return true;
}

void Map::Set_position(Vector2D pos) {				// p값 설정  -- Set_pos 분리하기

	m_vPos = pos;

	Object2D::ScreenToNDC();			// 화면 좌표계 -> NDC 좌표계

	UpdateVertextBuffer();
}


void Map::Set_position(Vector2D pos, Vector2D cam_pos) {				// p값 설정  -- Set_pos 분리하기

	m_vPos = pos;

	ScreenToCam(cam_pos, m_vViewSize);			// 월드 좌표 -> 뷰 좌표 -> NDC 좌표

	UpdateVertextBuffer();
}

void Map::ScreenToCam(Vector2D cam_pos, Vector2D view_size) {

	Vector2D View_pos = m_vPos;			// 오브젝트 pos (월드 좌표) 기준으로 변환

	View_pos.x = View_pos.x - cam_pos.x;
	View_pos.y = View_pos.y - cam_pos.y;

	m_vDrawPos.x = (View_pos.x / view_size.x) * 2.0f;			// View pos 기준으로 NDC로 변환
	m_vDrawPos.y = -((View_pos.y / view_size.y) * 2.0f);		// 클라이언트 크기에 맞춰 -1~1 정규화하지 않음
	m_vDrawSize.x = (m_rtInit.w / view_size.x) * 2;
	m_vDrawSize.y = (m_rtInit.h / view_size.y) * 2;

}

void Map::UpdateVertextBuffer() {

	float x1 = m_vDrawPos.x;
	float y1 = m_vDrawPos.y;
	float w1 = m_vDrawSize.x;
	float h1 = m_vDrawSize.y;

	m_VertexList[0].p = { x1, y1, 0.0f };
	//m_VertexList[0].t = { m_rtUV.x,  m_rtUV.y };
	m_VertexList[0].t = { 0.0f,0.0f };

	m_VertexList[1].p = { x1 + w1, y1, 0.0f };
	//m_VertexList[1].t = { m_rtUV.x + m_rtUV.w,  m_rtUV.y };
	m_VertexList[1].t = { 1.0f,0.0f };

	m_VertexList[2].p = { x1, y1 - h1, 0.0f };
	//m_VertexList[2].t = { m_rtUV.x,  m_rtUV.y + m_rtUV.h };
	m_VertexList[2].t = { 0.0f,1.0f };

	m_VertexList[3].p = { x1 + w1, y1 - h1, 0.0f };
	//m_VertexList[3].t = { m_rtUV.x + m_rtUV.w ,m_rtUV.y + m_rtUV.h };
	m_VertexList[3].t = { 1.0f,1.0f };

	m_pImmediateContext->UpdateSubresource(m_pVertexBuffer, NULL, NULL, &m_VertexList.at(0), 0, 0);

}