#include "Device.h"


class Sample : public Device
{
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
public:
	Sample();
	~Sample();
};

