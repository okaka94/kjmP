#pragma once
#include <fbxsdk.h>
#include "Shape.h"

struct Anim_track {
	UINT	frame;
	//TBASIS_EX::TMatrix		Anim_matrix;			// 부모 * 자신
	//TBASIS_EX::TMatrix		Pure_Anim_matrix;		// 자신
	//TBASIS_EX::TVector3		T;
	//TBASIS_EX::TQuaternion	R;
	//TBASIS_EX::TVector3		S;
	Matrix		Anim_matrix;
	Matrix		Pure_Anim_matrix;
	Vector		T;
	Quaternion	R;
	Vector		S;
};

struct Anim_scene {
	UINT			Start_frame;
	UINT			End_frame;
	float			TickPerFrame;		// 프레임당 틱 (보통 160)
	float			Frame_speed;		// 초당 프레임 (보통 30fps)
	FbxTime::EMode  Time_mode;

};

struct Weight {
	std::vector<int>  Index;
	std::vector<float>  weight;
	void Insert(int iBone, float fWeight)
	{
		for (int i = 0; i < Index.size(); i++)
		{
			if (fWeight > weight[i])
			{
				for (int j = Index.size() - 1; j > i; --j)
				{
					Index[j] = Index[j - 1];
					weight[j] = weight[j - 1];
				}
				Index[i] = iBone;
				weight[i] = fWeight;
				break;
			}
		}
	}
	Weight()
	{
		Index.resize(8);
		weight.resize(8);
	}
};

class FBX_obj : public Object3D
{
/// ////// FBX Loader로 분리 필요
public:
	UINT					m_Object_Bone;
	Matrix					m_obj_Anim_matrix;
	FbxAMatrix				m_fbx_local_mat;
	std::vector<Anim_track> m_Anim_track_list;
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
	std::vector<ID3D11Buffer*>					m_SubVB_list;
	std::vector<std::vector<PNCTVertex>>		m_VBdata_list;
	std::vector<Texture*>						m_SubTEX_list;
	std::vector<W_STR>							m_SubTEX_name_list;
public:
	void	CreateVertexList();
	HRESULT	CreateVertexBuffer();
	HRESULT	CreateIndexBuffer();
	bool	LoadTexture(std::wstring filename);
	bool	Post_Render();
	bool	Release();
	Matrix	Interpolate(float frame, Anim_scene anim_scene);
	

};

class Skinning_FBX_obj : public FBX_obj {

public:
	bool		m_skinned = false;
	// sub material
	std::vector<ID3D11Buffer*>				m_SubVB_list_IW;
	std::vector<std::vector<IW_VERTEX>>		m_VBdata_list_IW;
	// single model
	std::vector<IW_VERTEX>					m_Vertex_list_IW;
	ID3D11Buffer*							m_VB_IW;
	// skinning
	std::vector<Weight>						m_Weight_list;
	std::map<UINT, Matrix>					m_Bindpose_mat_map;
public:
	VS_BONE_CONSTANT_BUFFER					m_bone_cbData;
	ID3D11Buffer*							m_Skin_Bone_CB;
public:
	HRESULT	CreateConstantBuffer()
	{
		Base_object::CreateConstantBuffer();

		HRESULT hr;
		for (int Bone = 0; Bone < 255; Bone++)
		{
			m_bone_cbData.Bone_mat[Bone].Set_I_matrix();
		}

		D3D11_BUFFER_DESC       bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.ByteWidth = sizeof(VS_BONE_CONSTANT_BUFFER) * 1; // 바이트 용량
		// GPU 메모리에 할당
		bd.Usage = D3D11_USAGE_DEFAULT; // 버퍼의 할당 장소 내지는 버퍼용도
		bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

		D3D11_SUBRESOURCE_DATA  sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = &m_bone_cbData;
		hr = m_pd3dDevice->CreateBuffer(
			&bd, // 버퍼 할당
			&sd, // 초기 할당된 버퍼를 체우는 CPU메모리 주소
			&m_Skin_Bone_CB);
		return hr;
	}
	HRESULT CreateVertexLayout()
	{
		HRESULT hr;
		if (m_pVSCode == nullptr)
		{
			return E_FAIL;
		}
		// 정점레이아웃은 정점쉐이더 밀접한 관련.
		// 정점레이아웃 생성시 사전에 정점쉐이더 생성이 필요하다.
		D3D11_INPUT_ELEMENT_DESC ied[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,0,D3D11_INPUT_PER_VERTEX_DATA, 0},
			{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT,   0,12,D3D11_INPUT_PER_VERTEX_DATA, 0},
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,24,D3D11_INPUT_PER_VERTEX_DATA, 0},
			{ "TEXTURE", 0, DXGI_FORMAT_R32G32_FLOAT,    0,40,D3D11_INPUT_PER_VERTEX_DATA, 0},

			{ "INDEX", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1,0,D3D11_INPUT_PER_VERTEX_DATA, 0},
			{ "WEIGHT", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1,16,D3D11_INPUT_PER_VERTEX_DATA, 0},
		};
		UINT NumElements = sizeof(ied) / sizeof(ied[0]);
		hr = m_pd3dDevice->CreateInputLayout(ied, NumElements, m_pVSCode->GetBufferPointer(), m_pVSCode->GetBufferSize(), &m_pVertexLayout);
		

		return hr;
	}

	HRESULT CreateVertexBuffer()
	{
		HRESULT hr = S_OK;;
		FBX_obj::CreateVertexBuffer();

		if (m_VBdata_list_IW.size() > 0)
		{
			m_SubVB_list_IW.resize(m_VBdata_list_IW.size());
			for (int ivb = 0; ivb < m_VBdata_list_IW.size(); ivb++)
			{
				if (m_VBdata_list_IW[ivb].size() > 0)
				{
					m_SubVB_list_IW[ivb] =
						ReturnVertexBuffer(m_pd3dDevice,
							&m_VBdata_list_IW[ivb].at(0),
							m_VBdata_list_IW[ivb].size(),
							sizeof(IW_VERTEX));
				}
			}
		}
		else
		{
			m_VB_IW =
				ReturnVertexBuffer(m_pd3dDevice,
					&m_Vertex_list_IW.at(0),
					m_Vertex_list_IW.size(),
					sizeof(IW_VERTEX));
		}
		return hr;
	}

	bool	Post_Render()
	{
		
		if (m_pIndexBuffer == nullptr)
		{
			if (m_VBdata_list.size() > 0)
			{
				for (int iSubObj = 0; iSubObj < m_SubVB_list.size(); iSubObj++)
				{
					if (m_VBdata_list[iSubObj].size() <= 0) continue;
					UINT stride[2] = { sizeof(PNCTVertex), sizeof(IW_VERTEX) }; // 정점1개의 바이트용량
					UINT offset[2] = { 0, 0 }; // 정점버퍼에서 출발지점(바이트)
					//SLOT(레지스터리)
					ID3D11Buffer* buffer[2] = { m_SubVB_list[iSubObj],m_SubVB_list_IW[iSubObj] };
					m_pImmediateContext->IASetVertexBuffers(0, 2, buffer, stride, offset);


					if (m_SubTEX_list.size() > 0 && m_SubTEX_list[iSubObj] != nullptr)
					{
						m_pImmediateContext->PSSetShaderResources(0, 1, &m_SubTEX_list[iSubObj]->m_pTextureSRV);
					}
					m_pImmediateContext->Draw(m_VBdata_list[iSubObj].size(), 0);
				}
			}
			else
			{
				UINT stride[2] = { sizeof(PNCTVertex), sizeof(IW_VERTEX) }; // 정점1개의 바이트용량
				UINT offset[2] = { 0, 0 }; // 정점버퍼에서 출발지점(바이트)
				//SLOT(레지스터리)
				ID3D11Buffer* buffer[2] = { m_pVertexBuffer,m_VB_IW };
				m_pImmediateContext->IASetVertexBuffers(0, 2, buffer, stride, offset);
				m_pImmediateContext->Draw(m_VertexList.size(), 0);
			}
		}
		else
		{
			m_pImmediateContext->DrawIndexed(m_IndexList.size(), 0, 0);
		}
		return true;
	}

	bool	Release()
	{
		if (m_Skin_Bone_CB)
		{
			m_Skin_Bone_CB->Release();
			m_Skin_Bone_CB = nullptr;
		}
		if (m_VB_IW)
		{
			m_VB_IW->Release();
			m_VB_IW = nullptr;
		}
		for (int iSubObj = 0; iSubObj < m_SubVB_list_IW.size(); iSubObj++)
		{
			if (m_SubVB_list_IW[iSubObj])
			{
				m_SubVB_list_IW[iSubObj]->Release();
				m_SubVB_list_IW[iSubObj] = nullptr;
			}
		}
		m_SubVB_list_IW.clear();

		FBX_obj::Release();
		return true;
	}
};


