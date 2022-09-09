#pragma once
#include "Quad_tree.h"
#include "Octree.h"
#include "Player_object.h"
#include "Map_object.h"
#include "NPC_object.h"


class Game_core
{
public:	
	ID3D11Device*				     m_pd3dDevice = nullptr;
	ID3D11DeviceContext*			 m_pImmediateContext = nullptr;
	Base_object*					 player;	
	Space_partition*				 World_sp;
	std::map<int, Base_object*>		 All_object_list;
	std::map<int, Base_object*>		 NPC_object_list;
	std::vector<Base_object*>		 Drawing_list;

	

public:
	void SetDevice(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext);
	void Get_instance(int type);
	void Set_default();
	bool Init();
	bool Frame(float delta_time);
	bool Render();
	bool Release();
	bool Run();
	
};
