#pragma once
#include "Game_core.h"
#include "FBX_loader.h"
#include "Camera_debug.h"
#include "FBX_char.h"


class Sample : public Game_core
{
public:
	std::map<std::wstring, UINT> m_fbx_table;
	std::vector<FBX_loader*> m_fbx_list;
	Camera_debug* Main_cam;
	UINT		_actionIdx = 0;

	FBX_char*				User_char;
	
	// create instance
	ImGui::FileBrowser	_fileDlg;
	std::string			_filePath;
	std::string			_fileName;

	
public:
	virtual bool Init() override;
	virtual bool Frame() override;
	virtual bool Render() override;
	virtual bool Release() override;
	void    ClearD3D11DeviceContext(ID3D11DeviceContext* pd3dDeviceContext);
	

	bool fbxGetter(void* data, int index, const char** output)
	{
		FBX_loader* fbx = (FBX_loader*)data;
		FBX_loader& currentFbx = fbx[index];
		*output = currentFbx._fileName.c_str();
	}

};

