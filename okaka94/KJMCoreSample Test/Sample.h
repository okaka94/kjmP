#pragma once
#include "Device.h"

class Sample : public Device
{
public:
	virtual bool Init() override;
	virtual bool Frame() override;
	virtual bool Render() override;
	virtual bool Release() override;
	virtual bool Run() override;
};

