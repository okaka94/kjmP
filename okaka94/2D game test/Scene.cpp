#include "Scene.h"

bool Scene::Set_device(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext) {
	m_pd3dDevice = pd3dDevice;
	m_pImmediateContext = pImmediateContext;

	return true;
}


bool Scene::Check_click(UI* button, POINT& cursor) {
	//if (button->m_vPos.x <= cursor.x) {
	//	if (button->m_vPos.x + button->m_rtInit.w >= cursor.x + 2) {
	//		if (button->m_vPos.y <= cursor.y) {
	//			if (button->m_vPos.y + button->m_rtInit.h >= cursor.y + 2) {

	//				return true;
	//			}
	//		}
	//	}
	//}

	if (button->m_vPos.x <= cursor.x) {
		if (button->m_vPos.x + button->UI_size.x >= cursor.x + 2) {
			if (button->m_vPos.y <= cursor.y) {
				if (button->m_vPos.y + button->UI_size.y >= cursor.y + 2) {

					return true;
				}
			}
		}
	}
	return false;
}