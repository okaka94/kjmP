#include "Window.h"

class Sample : public Window
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

