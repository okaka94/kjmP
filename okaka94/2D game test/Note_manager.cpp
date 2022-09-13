#include "Note_manager.h"

void Note_manager::SetDevice(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pContext) {
	m_pd3dDevice = pd3dDevice;
	m_pImmediateContext = pContext;
}

void Note_manager::Load_texture() {
	m_pMask = Texture_manager::GetInstance().Load(L"../../data/EBA/Note_mask.bmp");
}	

void Note_manager::Create(std::wstring index, Vector2D pos) {
	// Create 하면서 사용중인 노드가 맞는지 체크 후 Create 단계로 넘어가기
	// but 항상 create을 호출하게 되므로 다른 방법 있는지 찾아볼 것
}

void Note_manager::Create_note(std::wstring index) {
	Note* pNew = new Note;
	pNew->Create(m_pd3dDevice, m_pImmediateContext,
		L"../../data/shader/DefaultShape_Mask.txt", L"../../data/EBA/Note.bmp");
	m_qNote_list.push(pNew);
	m_qNote_list.front()->Set_rect(B0);
}
void Note_manager::Deploy_note(Vector2D pos) {
	m_qNote_list.front()->Set_position({ 100,100 });
}
void Note_manager::Judge_note() {

}
void Note_manager::Release_note() {
	m_qNote_list.front()->Release();
	m_qNote_list.pop();
}

void Note_manager::Release() {
	while (!m_qNote_list.empty()) {
		m_qNote_list.front()->Release();
		m_qNote_list.pop();
	}
}

Note_manager::Note_manager() {}

Note_manager::~Note_manager() {

	Release();
}