#pragma once
#include "BlueWin.h"
#include "ThreadManager.h"

class Keyboard;
class InputManager
{
public:
	InputManager() {}
	~InputManager() {}

private:
	void InputThread();
private:
	Keyboard* windowKeyboard;
	bool runThread = true;
};
