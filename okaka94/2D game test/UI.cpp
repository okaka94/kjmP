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