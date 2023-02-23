#pragma once
#include "Base_object.h"
#include "Quad_tree.h"

class Map : public Base_object
{
public:
	DWORD					faces_num;
	DWORD					rows_num;
	DWORD					cols_num;
	Quad_tree				Map_Qtree;
public:		// height map
	std::vector<float>		m_Height_list;
	float					max_Height = 100.0f;
	float					cell_size = 2.0f;

public:
	bool Build(ID3D11Device* pd3dDevice , UINT width, UINT height, Camera* cam);
	bool Create_Qtree(ID3D11Device* pd3dDevice, Camera* cam);
	bool Render() override;

	bool Load_height_map(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pContext, W_STR Texture);
	void Gen_vertex_n();
	Vector Calc_face_normal(UINT i0, UINT i1, UINT i2);
	float Get_height(float x, float z);
	float Get_height_map(int row, int col);
	float Lerp(float fStart, float fEnd, float fTangent);


};

