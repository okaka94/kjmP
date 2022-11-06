#pragma once
#include "Texture.h"
class Texture_manager : public Singleton<Texture_manager>
{
public:
	ID3D11Device* m_pd3dDevice = nullptr;
	ID3D11DeviceContext* m_pImmediateContext = nullptr;
	void SetDevice(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pContext);
private:
	friend class Singleton<Texture_manager>;
	std::map<std::wstring, Texture*> m_List;
public:
	Texture* Load(std::wstring name);
	Texture* Find(std::wstring name);
	bool Release();
	W_STR		Get_split_name(std::wstring fullpath);
	W_STR		Get_split_name(std::string fullpath);
private:
	Texture_manager();
public:
	~Texture_manager();
};

