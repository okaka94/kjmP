#pragma once
#include "Device.h"
#include "Input.h"


class Game_core : public Device
{
public:
	bool		m_game_run = true;
public:	
	//ID3D11Device*				     m_pd3dDevice = nullptr;
	//ID3D11DeviceContext*			 m_pImmediateContext = nullptr;

	//Base_object*					 player;	
	//Space_partition*				 World_sp;
	//std::map<int, Base_object*>		 All_object_list;
	//std::map<int, Base_object*>		 NPC_object_list;
	//std::vector<Base_object*>		 Drawing_list;

	

public:
	//void SetDevice(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext);
	//void Get_instance(int type);
	//void Set_default();
	
	bool CoreInit();
	bool CoreFrame();

	bool CorePre_Render();						// Rendering ¼¼ºÐÈ­
	bool CoreRender();
	bool CorePost_Render();

	bool CoreRelease();

public:
	virtual bool Init() { return true; };
	virtual bool Frame() { return true; };
	virtual bool Render() { return true; };
	virtual bool Release() { return true; };
	bool		 Run();
	
};
