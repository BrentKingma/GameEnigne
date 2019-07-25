#pragma once
#include "BlueWin.h"
#include "InputMain.h"
#include "Window.h"


class GraphicsMain
{

public:
	GraphicsMain() noexcept;
	~GraphicsMain() {}
	int InitializeGraphics(int width, int height, const char* name);
	int DestroyAll();
	Window* GetWindow() const noexcept;

private:
	Window* myWindow;
	int numActiveWindows = 0;
};