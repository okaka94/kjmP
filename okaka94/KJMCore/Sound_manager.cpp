#include "Sound_manager.h"
#include <tchar.h>
#include <io.h>  // _findclose

void Sound_manager::Load_dir(std::wstring path) {
	W_STR dirpath = path + L"*.*";
	intptr_t handle;
	struct _wfinddata_t fd;
	handle = _wfindfirst(dirpath.c_str(), &fd);
	if (handle == -1L) return;

	do {
		if ((fd.attrib & _A_SUBDIR) && fd.name[0] != '.') {
			Load_dir(path + fd.name + L"/");
		}
		else if (fd.name[0] != '.') {
			m_File_list.push_back(path + fd.name);
		}
	} while (_wfindnext(handle, &fd) == 0);
	_findclose(handle);
}

void Sound_manager::Load_all(std::wstring path) {
	Load_dir(path);
	for (auto& data : m_File_list) {
		Load(data);
	}
}

Sound* Sound_manager::Get_ptr(W_STR name) {
	
	auto iter = m_List.find(name);
	if (iter != m_List.end()) {
		Sound* pSound = iter->second;
		return pSound;
	}
	return nullptr;
}

bool Sound_manager::Init() {
	FMOD::System_Create(&m_pSystem);
	m_pSystem->init(32, FMOD_INIT_NORMAL, 0);
	return true;
}

W_STR Sound_manager::Get_split_name(std::wstring fullpath) {
	W_STR result;
	TCHAR drive[MAX_PATH] = { 0, };
	TCHAR dir[MAX_PATH] = { 0, };
	TCHAR filename[MAX_PATH] = { 0, };
	TCHAR ext[MAX_PATH] = { 0, };			 // . 포함 확장자명
	_tsplitpath_s(fullpath.c_str(), drive, dir, filename, ext);
	result = filename;
	result += ext;
	return result;
}

Sound* Sound_manager::Load(std::wstring fullpath) {

	HRESULT hr;
	W_STR name = Get_split_name(fullpath);

	auto iter = m_List.find(name);
	if (iter != m_List.end()) {
		return iter->second;
	}
	Sound* New_data = new Sound;
	New_data->m_Path = fullpath;
	if (New_data) {
		hr = New_data->Load(m_pSystem, fullpath); // sound_mgr을 거쳐서 로드하기때문에 system 포인터 전달해줘야 함 (set_device 역할)
		if (SUCCEEDED(hr)) {
			m_List.insert(std::make_pair(name, New_data));
		}
	}
	return New_data;
}

bool Sound_manager::Frame() {

	m_pSystem->update();
	for (auto data : m_List) {
		Sound* pData = data.second;
		if (pData) pData->Frame();
	}
	return true;
}

Sound_manager::Sound_manager(){}

bool Sound_manager::Release() {
	for (auto data : m_List) {
		Sound* pData = data.second;
		if (pData) pData->Release();
		delete pData;
	}
	m_pSystem->close();
	m_pSystem->release();
	m_List.clear();
	return true;
}

Sound_manager::~Sound_manager() {
	Release();
}