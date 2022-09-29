#pragma once
#include "Scene.h"


class Ingame_scene : public Scene
{
public:
	
	Base_object* BG;
	float	current_time = -1.0f;
	float	offset;
	int		Beat_counter = 1;
	int		BPM;
public:
	//virtual bool Set_device(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext);
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();
};

