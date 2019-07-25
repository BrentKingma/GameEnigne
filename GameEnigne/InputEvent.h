#pragma once
#include <Windows.h>
#include "KeyCodes.h"
struct InputEventData
{
	HWND hwnd = nullptr;
	EventType eventType = EventType::NO_TYPE;
	KeyCode mainKey = KeyCode::NO_CODE;
	bool shiftPressed = false;
	bool ctrlPressed = false;
	bool altPressed = false;
	bool wasDown = false;
public:
	InputEventData() {}
};

class InputEvent
{
public:
	virtual ~InputEvent() {}
	EventType	getEventType()	const { return _inputEventData.eventType; }
	HWND		getSource()		const { return _inputEventData.hwnd; }
	KeyCode		getKeyCode()	const { return _inputEventData.mainKey; }
	bool		isAltDown()		const { return _inputEventData.altPressed; }
	bool		isShiftDown()	const { return _inputEventData.shiftPressed; }
	bool		isCtrlDown()	const { return _inputEventData.ctrlPressed; }
	bool		wasDown()		const { return _inputEventData.wasDown; }

	void		setData(InputEventData ie) { _inputEventData = ie; }
private:
	InputEventData _inputEventData;
};
