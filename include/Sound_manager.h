#pragma once
#include "Sound.h"

class Sound_manager : public Singleton<Sound_manager>
{
	FMOD::System*				m_pSystem = nullptr;
	std::list<std::wstring>		m_File_list;		// Full-Path & Filename
private:
	friend class Singleton<Sound_manager>;
	std::map<std::wstring, Sound*> m_List;			// Indexing with Filename
public:
	T_STR		Get_split_name(std::wstring fullpath);
	void		Load_dir(std::wstring path);
	void		Load_all(std::wstring path);
	bool		Init();
	bool		Frame();
	Sound*		Load(std::wstring fullpath);
	bool		Release();
	Sound*		Get_ptr(W_STR name);				// 다른 매니저 Find 대체
private:
	Sound_manager();
public:
	~Sound_manager();
};

