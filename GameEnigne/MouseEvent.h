#pragma once
#include "InputEvent.h"

struct MouseEventData
{
	unsigned short screenXPOS = 0;
	unsigned short screenYPOS = 0;
	unsigned short windowX = 0;
	unsigned short windowY = 0;

	bool isMiddleDown = false;
	bool isLeftDown = false;
	bool isRightDown = false;

	KeyCode mouseButtonCode = KeyCode::NO_CODE;

	MouseEventData() {}
};

class MouseEvent : public InputEvent
{
public:
	unsigned short getScreenXPOS() { return _mouseEventData.screenXPOS; }
	unsigned short getScreenYPOS() { return _mouseEventData.screenYPOS; }
	unsigned short getWindowX() { return _mouseEventData.windowX; }
	unsigned short getWindowY() { return _mouseEventData.windowY; }

	bool isMiddleMouseDown() { return _mouseEventData.isMiddleDown; }
	bool isLeftMouseDown() { return _mouseEventData.isLeftDown; }
	bool isRightMouseDown() { return _mouseEventData.isRightDown; }

	KeyCode getButtonCode() { return _mouseEventData.mouseButtonCode; }

	void setMouseData(MouseEventData md) { _mouseEventData = md; }

private:
	MouseEventData _mouseEventData;
};

