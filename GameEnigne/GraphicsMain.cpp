#include "GraphicsMain.h"
#include "WindowsMessageMap.h"

GraphicsMain::GraphicsMain() noexcept
{
	myWindow = nullptr;
}

int GraphicsMain::InitializeGraphics(int width, int height, const char* name)
{
	try
	{
		myWindow = new Window(width, height, name);
		if (myWindow == nullptr)
		{
			throw myWindow;
		}
	}
	catch(Window*)
	{
		PostQuitMessage(1);
	}

	return 0;
}

int GraphicsMain::DestroyAll()
{
	myWindow->~Window();
	return 0;
}

Window* GraphicsMain::GetWindow() const noexcept
{
	return myWindow;
}