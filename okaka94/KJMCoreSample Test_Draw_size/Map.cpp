#include "Map.h"

bool Map::Frame() {

	Set_position(m_vPos);



	return true;
}

bool Map::Fix_t() {

	

	

	m_vDrawPos.x = (m_vPos.x / g_rtClient.right) * 2.0f - 1.0f;
	m_vDrawPos.y = -((m_vPos.y / g_rtClient.bottom) * 2.0f - 1.0f);
	m_vDrawSize.x = (m_rtInit.w / g_rtClient.right) * 2;
	m_vDrawSize.y = (m_rtInit.h / g_rtClient.bottom) * 2;

	float x1 = m_vDrawPos.x;
	float y1 = m_vDrawPos.y;
	float w1 = m_vDrawSize.x;
	float h1 = m_vDrawSize.y;

	m_VertexList[0].p = { x1, y1, 0.0f };
	m_VertexList[0].t = {0,0 };

	m_VertexList[1].p = { x1 + w1, y1, 0.0f };
	m_VertexList[1].t = { 1,0 };

	m_VertexList[2].p = { x1, y1 - h1, 0.0f };
	m_VertexList[2].t = { 0,1 };

	m_VertexList[3].p = { x1 + w1, y1 - h1, 0.0f };
	m_VertexList[3].t = {1,1 };

	m_pImmediateContext->UpdateSubresource(m_pVertexBuffer, NULL, NULL, &m_VertexList.at(0), 0, 0);

	return true;
}

bool Map::Control_drawsize(Vector2D modifier) {





	m_vDrawPos.x = (m_vPos.x / g_rtClient.right) * 2.0f - 1.0f;
	m_vDrawPos.y = -((m_vPos.y / g_rtClient.bottom) * 2.0f - 1.0f);

	//m_vDrawPos.x = (m_vPos.x / modifier.x) * 2.0f - 1.0f;
	//m_vDrawPos.y = -((m_vPos.y / modifier.y) * 2.0f - 1.0f);
	m_vDrawSize.x = (m_rtInit.w / modifier.x) * 2;
	m_vDrawSize.y = (m_rtInit.h / modifier.y) * 2;

	float x1 = m_vDrawPos.x;
	float y1 = m_vDrawPos.y;
	float w1 = m_vDrawSize.x;
	float h1 = m_vDrawSize.y;

	m_VertexList[0].p = { x1, y1, 0.0f };
	m_VertexList[0].t = { m_rtUV.x,  m_rtUV.y };

	m_VertexList[1].p = { x1 + w1, y1, 0.0f };
	m_VertexList[1].t = { m_rtUV.x + m_rtUV.w,  m_rtUV.y };

	m_VertexList[2].p = { x1, y1 - h1, 0.0f };
	m_VertexList[2].t = { m_rtUV.x,  m_rtUV.y + m_rtUV.h };

	m_VertexList[3].p = { x1 + w1, y1 - h1, 0.0f };
	m_VertexList[3].t = { m_rtUV.x + m_rtUV.w ,m_rtUV.y + m_rtUV.h };

	m_pImmediateContext->UpdateSubresource(m_pVertexBuffer, NULL, NULL, &m_VertexList.at(0), 0, 0);

	return true;
}