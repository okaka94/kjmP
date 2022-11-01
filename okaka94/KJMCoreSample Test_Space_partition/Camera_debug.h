#pragma once
#include "Camera.h"

class Camera_debug : public Camera
{
public:

public:
	bool Frame() override;
	void Update_cam() override;   // add frustum create 
};

