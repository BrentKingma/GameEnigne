#include "App.h"
#include <sstream>
#include <iomanip>

App::App() : wnd(1280, 720, "Test Application")
{
	/*gm = GraphicsMain();
	gm.InitializeGraphics(1920, 1080, "Test Application");
	wnd = gm.GetWindow();*/
}

int App::Run()
{
	while (true)
	{
		if (const auto ecode = Window::ProcessMessages())
		{
			return *ecode;
		}
		Frame();
	}

	//gm.DestroyAll();
}

void App::Frame()
{

}
