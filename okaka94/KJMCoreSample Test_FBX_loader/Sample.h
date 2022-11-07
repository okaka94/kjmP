#pragma once
#include "Game_core.h"
#include "FBX_loader.h"
#include "Camera_debug.h"


class Sample : public Game_core
{
public:
	std::vector<FBX_loader*> m_fbx_list;
	Camera_debug* Main_cam;
			
public:
	virtual bool Init() override;
	virtual bool Frame() override;
	virtual bool Render() override;
	virtual bool Release() override;
	void    ClearD3D11DeviceContext(ID3D11DeviceContext* pd3dDeviceContext);

};

