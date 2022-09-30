#pragma once
#include "Sound_manager.h"
#include "Song_manager.h"
#include "Input.h"
#include "Writer.h"
#include "UI.h"
#include "Transition.h"

enum SCENE_SWITCH {
	TITLE,
	SELECT,
	INGAME,
	RESULT,
};

class Scene
{
public:
	SCENE_SWITCH	scene ;
	ID3D11Device* m_pd3dDevice = nullptr;
	ID3D11DeviceContext* m_pImmediateContext = nullptr;
public:
	Sound* Sound_effect = nullptr;			// effect , song�� �����̴ϱ� �θ� ���� �־�α�
	Sound* Song = nullptr;
	
public:
	virtual bool Check_click(UI* button, POINT& cursor);
	virtual bool Set_device(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext);
	virtual bool Init() { return true; }
	virtual bool Frame() { return true; }
	virtual bool Render() { return true; }
	virtual bool Release() { return true; }
};

