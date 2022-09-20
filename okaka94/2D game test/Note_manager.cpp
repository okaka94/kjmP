#include "Note_manager.h"

void Note_manager::Init() {
	
	Load_texture();
	Load_all_note();	// 아직 공백
	
	std::string name = "B0";
	Rect	pos = { 10,10 ,59, 59 };

	Tex_pos.insert(std::make_pair(name,pos));
	name = "B1";
	pos = { 70,10 , 59, 59 };
	Tex_pos.insert(std::make_pair(name, pos));

	name = "B2";
	pos = { 130,10 , 59, 59 };
	Tex_pos.insert(std::make_pair(name, pos));
	//Create_note("B0");
	//Create_note("B0");
	//Create_note("B1");


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
	t += 3.0f;
	pNew->set_time(t);
	

	static Vector2D pos = { 100,100 };

	

	pNew->Set_position(pos);
		pos.x += 30.0f;
		pos.y += 30.0f;
	


	m_Note_list.push_back(pNew);
	return true;
}
bool Note_manager::Deploy_note(Vector2D pos, float Ptime) {

	

	for (int i = 0; i < m_Note_list.size(); i++) {
		if (fabs(m_Note_list[i]->just_time - Ptime) < EPSILON) {
			m_Note_list[i]->Set_position(pos);
			return true;
		}
	}
	
	return false;

}

bool Note_manager::Check_click(Vector2D note, Vector2D cursor) {
	if (note.x <= cursor.x) {
		if (note.x +59  >= cursor.x + 2) {
			if (note.y <= cursor.y) {
				if (note.y + 59 >= cursor.y + 2) {
					return true;
				}
			}
		}
	}
	return false;
}

void Note_manager::Judge_note(float x, float y) {
	if (m_Note_list.empty()) return;
	
	
	
	Vector2D cursor(x, y);



	auto iter = m_Note_list.begin();
	int i = 0;
	while(iter != m_Note_list.end()) {
		if (Check_click(m_Note_list[i]->m_vPos, cursor))
			bool check = true;
		i++;
		iter++;
	}
}
void Note_manager::Release_note(float Ptime) {
	if (m_Note_list.empty()) return;
	
	else{
		for (int i = 0; i < m_Note_list.size(); i++) {
			if(Ptime - m_Note_list[0]->just_time <= 2.5f){
			m_Note_list[i]->Release();
			m_Note_list.erase(m_Note_list.begin() + i);
			//i--;
			}
		}
		
	}
	
}

void Note_manager::Release() {
	for (int i = 0; i < m_Note_list.size(); i++) {
		m_Note_list.front()->Release();
		m_Note_list.erase(m_Note_list.begin() + i);
	}
	m_Note_list.clear();
	Tex_pos.clear();

	
}

Note_manager::Note_manager() {}

Note_manager::~Note_manager() {

	Release();
}