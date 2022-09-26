#pragma once
#include "Note_manager.h"
#include "Info_struct.h"
class Song_manager : public Singleton<Song_manager>
{
public:
	Song_info				m_song_info;
	std::queue<Note_info>	m_noteQ;
private:
	friend class Singleton<Song_manager>;
	
public:
	bool Init();
	bool Load(std::wstring filename);
	//Song_info Get_Song_info() {
	//	return m_song_info;
	//}
	//std::queue<Note_info*> Get_noteQ() {
	//	return m_noteQ;
	//}
	void Release() {};
private:
	Song_manager() {};
public:
	~Song_manager() {};
};

