#pragma once
#include "Scene.h"
class Title_scene :  public Scene
{
public:
	Base_object*	Title;
	Base_object*	Play;
public:
	virtual bool Init();
	virtual bool Frame() { return true; }
	virtual bool Render();
	virtual bool Release();
};

