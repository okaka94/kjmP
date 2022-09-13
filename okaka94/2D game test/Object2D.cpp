#include "Object2D.h"

bool Object2D::Frame() { return true; }

Object2D::~Object2D() {}


void Object2D::UpdateVertextBuffer() {

	float x1 = m_vDrawPos.x;
	float y1 = m_vDrawPos.y;
	float w1 = m_vDrawSize.x;
	float h1 = m_vDrawSize.y;

	m_VertexList[0].p = { x1, y1, 0.0f };
	m_VertexList[0].t = {m_rtUV.x,  m_rtUV.y };

	m_VertexList[1].p = { x1 + w1, y1, 0.0f };
	m_VertexList[1].t = { m_rtUV.x+m_rtUV.w,  m_rtUV.y };

	m_VertexList[2].p = { x1, y1 - h1, 0.0f };
	m_VertexList[2].t = { m_rtUV.x,  m_rtUV.y+m_rtUV.h };

	m_VertexList[3].p = { x1 + w1, y1 - h1, 0.0f };
	m_VertexList[3].t = { m_rtUV.x + m_rtUV.w ,m_rtUV.y + m_rtUV.h };

	m_pImmediateContext->UpdateSubresource(m_pVertexBuffer, NULL, NULL, &m_VertexList.at(0), 0, 0);

}

void Object2D::Set_rect(Rect rt) {						// t값 설정
	
	m_rtInit = rt;
	m_ptImgSize.x = m_pTexture->m_Desc.Width;
	m_ptImgSize.y = m_pTexture->m_Desc.Height;

	m_rtUV.x = rt.x / m_ptImgSize.x;
	m_rtUV.y = rt.y / m_ptImgSize.y;
	m_rtUV.w = rt.w / m_ptImgSize.x;
	m_rtUV.h = rt.h / m_ptImgSize.y;
}

void Object2D::Set_rect(float x, float y, float w, float h) {						// t값 설정

	m_rtInit = { x,y,w,h };
	m_ptImgSize.x = m_pTexture->m_Desc.Width;
	m_ptImgSize.y = m_pTexture->m_Desc.Height;

	m_rtUV.x = x / m_ptImgSize.x;
	m_rtUV.y = y / m_ptImgSize.y;
	m_rtUV.w = w / m_ptImgSize.x;
	m_rtUV.h = h / m_ptImgSize.y;
}


void Object2D::Set_position(Vector2D pos) {				// p값 설정
	
	m_vPos = pos;
	
	m_vDrawPos.x = (pos.x / g_rtClient.right) * 2.0f - 1.0f;
	m_vDrawPos.y = -((pos.y / g_rtClient.bottom) * 2.0f - 1.0f);
	m_vDrawSize.x = (m_rtInit.w / g_rtClient.right) * 2;
	m_vDrawSize.y = (m_rtInit.h / g_rtClient.bottom) * 2;

	UpdateVertextBuffer();
}
