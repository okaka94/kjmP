#pragma once
#include <fbxsdk.h>
#include "Shape.h"

class FBX_obj : public Object3D
{
public:
	FbxNode*				m_pFbxNode = nullptr;
	FbxNode*				m_pFbxParentNode = nullptr;
	FBX_obj*				m_pParent = nullptr;
	std::vector< FBX_obj*>	m_Child_list;
	void Set_parent(FBX_obj* parent) {
		parent->m_Child_list.push_back(this);
		m_pParent = parent;
	}
public:
	std::vector<ID3D11Buffer*>				m_SubVB_list;
	std::vector<std::vector<PNCTVertex>		m_VBdata_list;
	std::vector<Texture*>					m_SubTEX_list;
	std::vector<W_STR>						m_SubTEX_name_list;
public:
	void	CreateVertexList();
	HRESULT	CreateVertexBuffer();
	HRESULT	CreateIndexBuffer();
	bool	LoadTexture(std::wstring filename);
	bool	Post_Render();
	bool	Release();
};

