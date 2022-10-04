#pragma once
#include "Scene.h"
class Result_scene :  public Scene
{
public:
	Base_object* BG;
	Sound*		 BGM;
	Transition*	 Screen;
public:
	bool Init();
	bool Frame();
	bool Render();// { return true; }
	bool Release(); // { return true; }
};

