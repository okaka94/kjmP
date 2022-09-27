#pragma once
#include "Sound_manager.h"
#include "Song_manager.h"
#include "Input.h"
#include "Writer.h"
class Scene
{
public:
	ID3D11Device* m_pd3dDevice = nullptr;
	ID3D11DeviceContext* m_pImmediateContext = nullptr;
public:
	Sound* Sound_effect = nullptr;			// effect , song은 공통이니까 부모 씬에 넣어두기
	Sound* Song = nullptr;
	
public:
	virtual bool Set_device(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext);
	virtual bool Init() { return true; }
	virtual bool Frame() { return true; }
	virtual bool Render() { return true; }
	virtual bool Release() { return true; }
};

