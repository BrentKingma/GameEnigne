#include "Window.h"
#include <sstream>
#include "resource.h"

Window::WindowClass Window::WindowClass::instance;

Window::WindowClass::WindowClass() noexcept : hInstance(GetModuleHandle(nullptr))
{
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = HandleMessageSetup;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = static_cast<HICON>(LoadImage(hInstance, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 256, 256, 0));
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = GetName();
	wc.hIconSm = static_cast<HICON>(LoadImage(hInstance, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 16, 16, 0));
	RegisterClassEx(&wc);
}

Window::WindowClass::~WindowClass()
{
	UnregisterClass(wndName, hInstance);
}

Window::Window(int width, int height, const char* name) :width(width), height(height)
{
	RECT wr;
	wr.left = 100;
	wr.right = width + wr.left;
	wr.top = 100;
	wr.bottom = height + wr.top;

	AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);
	//Creates window and gets HWND
	hWnd = CreateWindow(WindowClass::GetName(), name,
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT, wr.right - wr.left, wr.bottom - wr.top,
		nullptr, nullptr, WindowClass::GetInstance(), this/*Connects the class to the WinApi*/);
	if (hWnd == nullptr)
	{
		throw CHWND_LAST_EXCEPT();
	}
	//Display Window
	ShowWindow(hWnd, SW_SHOWDEFAULT);
}

Window::~Window()
{
	DestroyWindow(hWnd);
}

LRESULT CALLBACK Window::HandleMessageSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	if (msg == WM_NCCREATE)
	{
		//Extracts the window class from creation data
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		Window* const pWnd = static_cast<Window*>(pCreate->lpCreateParams);
		//Sets the pointer of the WinAPI managed class to the window class
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		//Sets the new message handler as the setup has finished
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::HandleMessageThunk));
		return pWnd->HandleMessages(hWnd, msg, wParam, lParam);
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT CALLBACK Window::HandleMessageThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	//Retrieves pointer to the window class
	Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	//Forwards message to the window class handler
	return pWnd->HandleMessages(hWnd, msg, wParam, lParam);
}

LRESULT Window::HandleMessages(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	switch (msg)
	{
		case WM_XBUTTONDOWN:
		{
		UINT button = GET_XBUTTON_WPARAM(wParam);
		if (button == XBUTTON1)
		{
			SetTitle("XBUTTON1");
		}
		else if (button == XBUTTON2)
		{
			SetTitle("XBUTTON2");
		}
		else
		{
			SetTitle("XBUTTON");
		}
		break;
	}
		case WM_CLOSE:
		{
		PostQuitMessage(0);
		return 0;
	}
		case WM_KILLFOCUS:
		{
		myKeyboard.ClearState();
		break;
	}
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
		{
		/*Bit 30 contains weather button was down already*/
		if (!(lParam != 0x40000000) || myKeyboard.IsAutoRepeatEnabled())
		{
			myKeyboard.OnKeyPressed(static_cast<unsigned char>(wParam));
		}
		break;
	}
		case WM_KEYUP:
		case WM_SYSKEYUP:
		{
		myKeyboard.OnKeyReleased(static_cast<unsigned char>(wParam));
		break;
	}
		case WM_CHAR:
		{
		myKeyboard.OnChar(static_cast<unsigned char>(wParam));
		break;
	}
		case WM_MOUSEMOVE:
		{
		const POINTS mousePoint = MAKEPOINTS(lParam);
		if (mousePoint.x >= 0 && mousePoint.x < width && mousePoint.y >= 0 && mousePoint.y < height)
		{
			myMouse.OnMouseMove(mousePoint.x, mousePoint.y);
			if (!myMouse.IsInWindow())
			{
				SetCapture(hWnd);
				myMouse.OnMouseEnter();
			}
		}
		else
		{
			if (wParam & (MK_LBUTTON | MK_RBUTTON))
			{
				myMouse.OnMouseMove(mousePoint.x, mousePoint.y);
			}
			else
			{
				ReleaseCapture();
				myMouse.OnMouseLeave();
			}
		}
		break;
	}
		case WM_LBUTTONDOWN:
		{
		const POINTS mousePoint = MAKEPOINTS(lParam);
		myMouse.OnLeftPressed(mousePoint.x, mousePoint.y);
		break;
	}
		case WM_LBUTTONUP:
		{
		const POINTS mousePoint = MAKEPOINTS(lParam);
		myMouse.OnLeftReleased(mousePoint.x, mousePoint.y);
		break;
	}
		case WM_RBUTTONDOWN:
		{
		const POINTS mousePoint = MAKEPOINTS(lParam);
		myMouse.OnRightPressed(mousePoint.x, mousePoint.y);
		break;
	}
		case WM_RBUTTONUP:
		{
		const POINTS mousePoint = MAKEPOINTS(lParam);
		myMouse.OnRightReleased(mousePoint.x, mousePoint.y);
		break;
	}
		case WM_MBUTTONDOWN:
		{
		const POINTS mousePoint = MAKEPOINTS(lParam);
		myMouse.OnWheelPressed(mousePoint.x, mousePoint.y);
		break;
	}
		case WM_MBUTTONUP:
		{
		const POINTS mousePoint = MAKEPOINTS(lParam);
		myMouse.OnWheelReleased(mousePoint.x, mousePoint.y);
		break;
	}
		case WM_MOUSEWHEEL:
		{
		const POINTS mousePoint = MAKEPOINTS(lParam);
		const int delta = GET_WHEEL_DELTA_WPARAM(wParam);
		myMouse.OnWheelDelta(mousePoint.x, mousePoint.y, delta);
		break;
	}
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

Window::Exception::Exception(int lineNum, const char* file, HRESULT hr) noexcept : BlueException(lineNum, file), hr(hr)
{}

const char* Window::Exception::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl
		<< "Error Code: " << GetErrorCode() << std::endl
		<< "Description: " << GetErrorString() << std::endl
		<< GetOriginString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char* Window::Exception::GetType() const noexcept
{
	return "Blue Graphics Window Exception";
}

std::string Window::Exception::TranslateErrorCode(HRESULT hr) noexcept
{
	char* messageBuffer = nullptr;
	///Creates windows allocated buffer and sets our pointer ^ to said windows buffer
	DWORD messageLength = FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		nullptr, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), reinterpret_cast<LPSTR>(&messageBuffer), 0, nullptr
	);
	if (messageLength == 0)
	{
		return "There is something very wrong cause I dont know the error code";
	}
	std::string errorTranslated = messageBuffer;
	///Frees windows allocated buffer
	LocalFree(messageBuffer);
	return errorTranslated;
}

HRESULT Window::Exception::GetErrorCode() const noexcept
{
	return hr;
}

std::string Window::Exception::GetErrorString() const noexcept
{
	return TranslateErrorCode(hr);
}

void Window::SetTitle(const std::string& name)
{
	if (SetWindowText(hWnd, name.c_str() )== 0)
	{
		throw CHWND_LAST_EXCEPT();
	}
}

std::optional<int> Window::ProcessMessages()
{
	MSG msg;
	if(PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
		{
			return msg.wParam;
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	//Return empty optional when not quitting app
	return{};
}