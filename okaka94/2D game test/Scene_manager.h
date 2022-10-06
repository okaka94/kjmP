#pragma once
#include "Std.h"

class Scene_manager : public Singleton<Scene_manager>
{
private:
	friend class Singleton<Scene_manager>;

public:
	SCENE_SWITCH state = TITLE;
	void Change_scene(SCENE_SWITCH scene) { state = scene; }
	SCENE_SWITCH Get_scene() { return state; }
private:
	Scene_manager() {};
public:
	~Scene_manager() {};
};

