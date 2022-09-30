#include "Transition.h"

bool Transition::Move_pos(int index, Vector2D pos) {
	if (m_Img.empty())	return false;

	m_Img[index]->m_vPos += pos;

	float x1 = (m_Img[index]->m_vPos.x / g_rtClient.right) * 2.0f - 1.0f;
	float y1 = -((m_Img[index]->m_vPos.y / g_rtClient.bottom) * 2.0f - 1.0f);
	//float w1 = (m_rtInit.w / g_rtClient.right) * 2;
	//float h1 = (m_rtInit.h / g_rtClient.bottom) * 2;
	float w1 = 2;
	float h1 = 2;

	m_Img[index]->m_VertexList[0].p = { x1, y1, 0.0f };
	m_Img[index]->m_VertexList[0].t = { 0,  0 };

	m_Img[index]->m_VertexList[1].p = { x1 + w1, y1, 0.0f };
	m_Img[index]->m_VertexList[1].t = { 1,  0 };

	m_Img[index]->m_VertexList[2].p = { x1, y1 - h1, 0.0f };
	m_Img[index]->m_VertexList[2].t = { 0,  1 };

	m_Img[index]->m_VertexList[3].p = { x1 + w1, y1 - h1, 0.0f };
	m_Img[index]->m_VertexList[3].t = { 1,  1 };

	m_Img[index]->m_pImmediateContext->UpdateSubresource(m_Img[index]->m_pVertexBuffer, NULL, NULL, &m_Img[index]->m_VertexList.at(0), 0, 0);



	return true;
}

bool Transition::Fade_img(int index, float alpha) {
	if (m_Img.empty())	return false;

	m_Img[index]->m_VertexList[0].c = { 1,1,1,alpha };
	m_Img[index]->m_VertexList[1].c = { 1,1,1,alpha };
	m_Img[index]->m_VertexList[2].c = { 1,1,1,alpha };
	m_Img[index]->m_VertexList[3].c = { 1,1,1,alpha };
	m_Img[index]->m_pImmediateContext->UpdateSubresource(m_Img[index]->m_pVertexBuffer, NULL, NULL, &m_Img[index]->m_VertexList.at(0), 0, 0);
	return true;
}


bool Transition::Frame() {

	//timer -= g_fSecPerFrame;
	//if (timer >= 0.0f) {
	//	pos.x -= m_rtInit.w * g_fSecPerFrame;
	//	Set_position({ pos.x,0 });
	//}


	

	return true;
}

bool Transition::Release() {
	if (m_Img.empty())	return false;

	for (int i = 0; i < m_Img.size(); i++) {
		UI* data = m_Img[i];
		delete data;
	}
	m_Img.clear();

	return true;
}