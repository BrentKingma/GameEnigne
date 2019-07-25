#include "BlueWin.h"
#include "ThreadManager.h"
#include "ThreadPool.h"
#include "App.h"

int CALLBACK WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance, 
	_In_ LPSTR lpCmdLine, 
	_In_ int nCmdShow)
{
	try
	{
		return App{}.Run();
	}
	catch (const BlueException& e)
	{
		MessageBox(nullptr, e.what(), e.GetType(), MB_OK | MB_ICONEXCLAMATION);
	}
	catch (const std::exception& e)
	{
		MessageBox(nullptr, e.what(), "Standard Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	catch (...)
	{
		MessageBox(nullptr, "No details on this exception", "Unknown", MB_OK | MB_ICONEXCLAMATION);
	}
	return -1;
}