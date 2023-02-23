#pragma once
#include "Game_core.h"
#include "FBX_loader.h"
#include "Camera_debug.h"
#include "FBX_char.h"
#include "Map.h"


class Sample : public Game_core
{
public:
	std::vector<FBX_loader*>		m_fbx_list;
	Camera_debug*					Main_cam;
	Map*							BG;
	//UINT		_actionIdx = 0;

	FBX_char*				User_char;
	
	// create instance
	ImGui::FileBrowser	_fileDlg;
	std::string			_filePath;
	std::string			_fileName;

	// key action
	std::map<char, FBX_loader*>	m_fbx_table;

	// debuging box
	Shape_box*			_box;
	
public:
	virtual bool Init() override;
	virtual bool Frame() override;
	virtual bool Render() override;
	virtual bool Release() override;
	void    ClearD3D11DeviceContext(ID3D11DeviceContext* pd3dDeviceContext);

};

