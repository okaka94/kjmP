#pragma once
#include "Scene.h"
class Result_scene :  public Scene
{
public:
	Base_object* BG;
	Sound*		 Click_ok;
	Sound*		 Click_bad;
	Transition*	 Screen;
	
public:
	
	bool Init();
	bool Frame();
	bool Render();// { return true; }
	bool Release(); // { return true; }
};

