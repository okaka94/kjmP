#include "Title_scene.h"

bool Title_scene::Init() {

	Title = new Base_object;
	Title->Create(m_pd3dDevice, m_pImmediateContext, L"../../data/shader/DefaultShape_Mask.txt", L"../../data/EBA/Img/Title.jfif");
	Play = new Base_object;
	Play->Create(m_pd3dDevice, m_pImmediateContext, L"../../data/shader/DefaultShape.txt", L"../../data/EBA/Img/guitar_a.jpg");
	
	return true;
}

bool Title_scene::Render() {

	Title->Render();
	Play->Render();
	
	return true;
}

bool Title_scene::Release() {

	Title->Release();
	Play->Release();

	return true;
}