#include "UI.h"

bool UI::Frame_btn() {

	timer += g_fSecPerFrame;

	static int i = 0;
	if (timer >= 0.07f) {
		
		
		if (i > 4) {
			
			i = 0;
			timer -= 1.5f;

		}
		Set_rect(sprite[i]);
		Set_position({ 320,490 }); // 가운데는 332
		i++;
		timer -= 0.07f;
	}
	
	

	//m_pImmediateContext->UpdateSubresource(m_pVertexBuffer, NULL, NULL, &m_VertexList.at(0), 0, 0);


	return true;
}

bool UI::Frame() {

	timer += g_fSecPerFrame;

	return true;
}



bool UI::Set_pos_size(Vector2D pos) {

	m_vPos.x = pos.x;
	m_vPos.y = pos.y;

	m_vDrawPos.x = (m_vPos.x / g_rtClient.right) * 2.0f - 1.0f;
	m_vDrawPos.y = -((m_vPos.y / g_rtClient.bottom) * 2.0f - 1.0f);
	m_vDrawSize.x = (UI_size.x / g_rtClient.right) * 2;
	m_vDrawSize.y = (UI_size.y / g_rtClient.bottom) * 2;

	UpdateVertextBuffer();

	return true;
}

bool UI::Set_UI_size(Vector2D size) {

	UI_size.x = size.x;
	UI_size.y = size.y;

	return true;
}
