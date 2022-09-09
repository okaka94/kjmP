#pragma once
#include "Shader.h"

class Shader_manager : public Singleton<Shader_manager>
{
public:
	ID3D11Device* m_pd3dDevice = nullptr;
	ID3D11DeviceContext* m_pImmediateContext = nullptr;
	void SetDevice(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pContext);
private:
	//friend class Singleton<Shader_manager>;
	std::map<std::wstring, Shader*> m_List;
public:
	Shader* Load(std::wstring name);
	bool Release();
private:
	Shader_manager();
public:
	~Shader_manager();
};

