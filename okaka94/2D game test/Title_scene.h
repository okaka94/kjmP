#pragma once
#include "Scene.h"
class Title_scene :  public Scene
{
public:
	UI*	Title;
	UI*	Play;
public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();
};

