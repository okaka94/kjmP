#pragma once
#include "Scene.h"
class Select_scene :public Scene
{
public:
	Base_object*		BG;
	Sound*				sample;
	std::vector<UI*>	album_list;
	std::vector<UI*>	info_list;
	UI*					Play;
	UI*					Left;
	UI*					Right;
public:
	bool Init(); 
	bool Frame();
	bool Render();// { return true; }
	bool Release(); // { return true; }
	
};

