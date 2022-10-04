#include "Note_manager.h"

void Note_manager::Init() {
	
	Load_texture();
	Load_all_note();	
	

}

bool Note_manager::Load_all_note() {

	Tex_pos.clear();
		

	TCHAR Buffer[256] = { 0, };
	TCHAR Temp[256] = { 0, };


	FILE* fp_src;
	//_wfopen_s(&fp_src, filename.c_str(), _T("rt"));
	_wfopen_s(&fp_src, L"../../data/EBA/Note_tex_pos.txt", _T("rt"));
	if (fp_src == NULL) return false;



	while (!feof(fp_src)) {
		_fgetts(Buffer, _countof(Buffer), fp_src);

		if (_tcscmp(Buffer, _T("[Pos_info]\n")) == 0) {

			while (!feof(fp_src)) {

				std::wstring name;
				Rect pos;

				_fgetts(Buffer, _countof(Buffer), fp_src);
				_stscanf_s(Buffer, _T("%s %f %f %f %f"), Temp, (unsigned int)_countof(Temp), &pos.x, &pos.y, &pos.w , &pos.h);
				name = Temp;

				Tex_pos.insert(std::make_pair(name, pos));
			}
		}


	}
	fclose(fp_src);
	return true;
}

void Note_manager::SetDevice(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pContext) {
	m_pd3dDevice = pd3dDevice;
	m_pImmediateContext = pContext;
}

void Note_manager::Load_texture() {
	m_pMask = Texture_manager::GetInstance().Load(L"../../data/EBA/Note_mask.bmp");
}	


bool Note_manager::Create_note(std::wstring note_type, Vector2D pos) {

	auto iter = Tex_pos.find(note_type);
	if (iter == Tex_pos.end() ) {
		return false;
	}
	


	Note* pNew = new Note;
	pNew->Create(m_pd3dDevice, m_pImmediateContext,
		L"../../data/shader/DefaultShape_Mask.txt", L"../../data/EBA/Note.bmp");
	
	pNew->Set_rect(iter->second);

	

	pNew->Set_position(pos);
	

	m_Note_list.push_back(pNew);
	return true;
}


bool Note_manager::Create_effect(const Note* note) {

	std::wstring effect_type = std::to_wstring(note->score);

	auto iter = Tex_pos.find(effect_type);
	if (iter == Tex_pos.end()) {
		return false;
	}



	Effect* pNew = new Effect;
	pNew->Create(m_pd3dDevice, m_pImmediateContext,
		L"../../data/shader/DefaultShape_Mask.txt", L"../../data/EBA/Note.bmp");

	Rect effect_rect = iter->second;

	pNew->Set_rect(effect_rect);

	
	Vector2D mod_pos;
	mod_pos.x = note->m_vPos.x - ((effect_rect.w - 59) / 2);
	mod_pos.y = note->m_vPos.y - ((effect_rect.h - 59) / 2);

	pNew->Set_position(mod_pos);


	m_Effect_list.push_back(pNew);
	return true;
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

bool Note_manager::Judge_note(float x, float y) {
	if (m_Note_list.empty()) return false;
	
	
	
	Vector2D cursor(x, y);



	auto iter = m_Note_list.begin();
	int i = 0;
	while(iter != m_Note_list.end()) {
		if (Check_click(m_Note_list[i]->m_vPos, cursor)) {
			if (i != 0) m_Note_list[0]->Set_fail();
			m_Note_list[0]->Set_state_false();  
			
			return true;
		}
			
		i++;
		iter++;
	}
	return false;
}
void Note_manager::Release_note() {
	if (m_Note_list.empty() && m_Effect_list.empty()) return;
	
	else{
		for (auto iter = m_Note_list.begin(); iter != m_Note_list.end(); )
		{
			Note* data = *iter;
			if (data->state==false)
			{
				// 노트 판정 일어나면 판정 이펙트 생성
				Create_effect(data);

				Score_manager::GetInstance().TotalScore += data->score;
				if (data->score != 0)
					Score_manager::GetInstance().ComboChain++;
				else
					Score_manager::GetInstance().ComboChain = 0;
				Score_manager::GetInstance().MaxCombo = max(Score_manager::GetInstance().MaxCombo, Score_manager::GetInstance().ComboChain);

				delete data;
				iter = m_Note_list.erase(iter);
				continue;
			}
			iter++;
		}

		for (auto iter = m_Effect_list.begin(); iter != m_Effect_list.end(); )
		{
			Effect* data = *iter;
			if (data->state == false)
			{
				delete data;
				iter = m_Effect_list.erase(iter);
				continue;
			}
			iter++;
		}
		
	}
	
}

void Note_manager::Release() {
	if (!m_Note_list.empty()) {
		for (auto iter = m_Note_list.begin(); iter != m_Note_list.end(); )
		{
			Note* data = *iter;
			delete data;
			iter = m_Note_list.erase(iter);
			continue;
			iter++;
		}
	}
	if (!m_Effect_list.empty()) {
		for (auto iter = m_Effect_list.begin(); iter != m_Effect_list.end(); )
		{
			Effect* data = *iter;
			delete data;
			iter = m_Effect_list.erase(iter);
			continue;
			iter++;
		}
	}
	
	m_Effect_list.clear();
	m_Note_list.clear();
	Tex_pos.clear();

	
}

Note_manager::Note_manager() {}

Note_manager::~Note_manager() {

	Release();
}