#pragma once
#include "Note.h"
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
	
	std::queue<Note*>	m_qNote_list;	// ��Ʈ ��ġ
	Texture*			m_pMask=nullptr;


public:
	void Init();
	void Load_all_note(){}			// Index, pos, time ������ �ִ� ����Ʈ�� �ε��ؼ� �ش� ���� ��� ��Ʈ ����
	void Load_texture();			// ����ũ �ؽ�ó �ε�
	void Create(std::string note_type, Vector2D pos, float time);
	bool Create_note(std::string note_type);
	

	void Deploy_note(Vector2D pos, float Ptime);	// Q front�� �ð������ ���� �� �ð� ���ؼ� ������ pos�� ��ġ
	void Judge_note();
	void Release_note(float Ptime);
	void Release();		
public:
	Texture* Get_pMask() {
		return m_pMask;
	}
	std::queue<Note*> Get_Q() {
		return m_qNote_list;
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
