#pragma once
#include "Note.h"
#include "Effect.h"
#include "Texture_manager.h"

class Note_manager : public Singleton<Note_manager>
{
public:
	ID3D11Device* m_pd3dDevice = nullptr;
	ID3D11DeviceContext* m_pImmediateContext = nullptr;
	void SetDevice(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pContext);
	std::map<std::string, Rect> Tex_pos;
private:
	friend class Singleton<Note_manager>;
	
	int					Total_score = 0;			// ���� ���ھ�
	std::vector<Note*>	m_Note_list;				// ��Ʈ ����Ʈ
	Texture*			m_pMask=nullptr;
	std::vector<Effect*> m_Effect_list;		// ����Ʈ ����Ʈ


public:
	void Init();
	void Load_all_note(){}			// Index, pos, time ������ �ִ� ����Ʈ�� �ε��ؼ� �ش� ���� ��� ��Ʈ ����
	void Load_texture();			// ����ũ �ؽ�ó �ε�
	//void Create(std::string note_type, Vector2D pos, float time);
	bool Create_note(std::string note_type);
	//bool Create_effect(std::string effect_type, Vector2D pos);
	bool Create_effect(const Note* note);
	void Judge_note(float x, float y);
	bool Check_click(Vector2D note, Vector2D cursor);
	void Release_note();
	void Release();		
public:
	Texture* Get_pMask() {
		return m_pMask;
	}
	std::vector<Note*> Get_list() {
		return m_Note_list;
	}
	std::vector<Effect*> Get_effect_list() {
		return m_Effect_list;
	}
private:
	Note_manager();
public:
	~Note_manager();
};




//#define B0 10,10  , 59, 59
//#define B1 70,10  , 59, 59
//#define B2 130,10 , 59, 59
//#define B3 190,10 , 59, 59
//#define B4 10,70  , 59, 59
//#define B5 70,70  , 59, 59
//#define B6 130,70 , 59, 59
//#define B7 190,70 , 59, 59
