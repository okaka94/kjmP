#include "Note_manager.h"

void Note_manager::Init() {
	
	Load_texture();
	Load_all_note();	// 아직 공백
	
	std::string name = "B0";
	Rect	pos = { 10,10 ,59, 59 };

	Tex_pos.insert(std::make_pair(name,pos));
	name = "B1";
	pos = { 130,10 , 59, 59 };
	Tex_pos.insert(std::make_pair(name, pos));

	Create_note("B0");
	Create_note("B0");
	Create_note("B1");
}

void Note_manager::SetDevice(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pContext) {
	m_pd3dDevice = pd3dDevice;
	m_pImmediateContext = pContext;
}

void Note_manager::Load_texture() {
	m_pMask = Texture_manager::GetInstance().Load(L"../../data/EBA/Note_mask.bmp");
}	

void Note_manager::Create(std::string note_type, Vector2D pos, float time) {
	// Create 하면서 사용중인 노드가 맞는지 체크 후 Create 단계로 넘어가기
	// but 항상 create을 호출하게 되므로 다른 방법 있는지 찾아볼 것
}


bool Note_manager::Create_note(std::string note_type) {

	auto iter = Tex_pos.find(note_type);
	if (iter == Tex_pos.end() ) {
		return false;
	}
	


	Note* pNew = new Note;
	pNew->Create(m_pd3dDevice, m_pImmediateContext,
		L"../../data/shader/DefaultShape_Mask.txt", L"../../data/EBA/Note.bmp");
	static float t = 3.0f;
	pNew->Set_rect(iter->second);
	pNew->set_time(t++);

	m_qNote_list.push(pNew);
	return true;
}
void Note_manager::Deploy_note(Vector2D pos, float Ptime) {
	if (fabs(m_qNote_list.front()->just_time - Ptime) < EPSILON )
	m_qNote_list.front()->Set_position(pos);
}
void Note_manager::Judge_note() {

}
void Note_manager::Release_note(float Ptime) {
	if (Ptime - m_qNote_list.front()->just_time >= 1.0f ) {
		m_qNote_list.front()->Release();
		m_qNote_list.pop();
	}
	
}

void Note_manager::Release() {
	while (!m_qNote_list.empty()) {
		m_qNote_list.front()->Release();
		m_qNote_list.pop();
	}
	Tex_pos.clear();

}

Note_manager::Note_manager() {}

Note_manager::~Note_manager() {

	Release();
}