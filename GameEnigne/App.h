#pragma once
#include "Window.h"
#include "BlueTime.h"

class App
{
public:
	App();
	int Run();
private:
	void Frame();
private:
	Window wnd;
	BlueTime timer;
};

