#pragma once
#include "Note.h"
#include "Texture_manager.h"

class Note_manager : public Singleton<Note_manager>
{
public:
	ID3D11Device* m_pd3dDevice = nullptr;
	ID3D11DeviceContext* m_pImmediateContext = nullptr;
	void SetDevice(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pContext);
private:
	friend class Singleton<Note_manager>;
	bool preemp[4][16] = { 0, };		// B , G , R , Y ������ ��Ʈ (0~15��) ������̸� true�� 
	std::queue<Note*>	m_qNote_list;	// ��Ʈ ��ġ
	Texture*			m_pMask=nullptr;
public:
	void Load_texture();			// ����ũ �ؽ�ó �ε�
	void Create(std::wstring index, Vector2D pos);
	void Create_note(std::wstring index);
	void Deploy_note(Vector2D pos);
	void Judge_note();
	void Release_note();
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


#define B0 10,10
#define B1 70,10
#define B2 130,10
#define B3 190,10
#define B4 10,70
#define B5 70,70
#define B6 130,70
#define B7 190,70
