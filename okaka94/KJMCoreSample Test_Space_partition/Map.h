#pragma once
#include "Base_object.h"
#include "Quad_tree.h"

class Map : public Base_object
{
public:
	DWORD        rows_num;
	DWORD        cols_num;
	Quad_tree	 Map_Qtree;
public:
	bool Build(ID3D11Device* pd3dDevice , UINT width, UINT height, Camera* cam);
	bool Create_Qtree(ID3D11Device* pd3dDevice, Camera* cam);
	bool Render() override;

};

