#pragma once
#include "Scene.h"


class Ingame_scene : public Scene
{
public:
	Base_object*	BG;
	Transition*		Insert;
	Sound*			Crowd;
	Transition*		Ingame_UI;
public:
	unsigned int before_time = 0;
	unsigned int ctime = 0;
	double count = 0;
	double current_time = -1.0f;
	float offset;
	int		Beat_counter = 1;
	double		BPM;
public:
	
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();
};

