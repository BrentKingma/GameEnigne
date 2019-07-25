#pragma once
#include "BlueWin.h"
#include "BlueException.h"
#include "Keyboard.h"
#include "Mouse.h"
#include <optional>

#define CHWND_EXCEPT(hr) Window::Exception(__LINE__,__FILE__,hr)
#define CHWND_LAST_EXCEPT() Window::Exception(__LINE__,__FILE__, GetLastError())

class Window
{
public:
	class Exception : public BlueException
	{
	public:
		Exception(int lineNum, const char* file, HRESULT hr) noexcept;
		const char* what() const noexcept override;
		const char* GetType() const noexcept override;
		static std::string TranslateErrorCode(HRESULT hr) noexcept;
		HRESULT GetErrorCode() const noexcept;
		std::string GetErrorString() const noexcept;
	private:
		HRESULT hr;
	};
private:
	class WindowClass
	{
	public:
		inline static const char* GetName() noexcept { return wndName; }
		inline static HINSTANCE GetInstance() noexcept { return instance.hInstance; }
	private:
		WindowClass() noexcept;
		WindowClass(const WindowClass&) = delete;
		~WindowClass();

		static constexpr const char* wndName = "Blue DX11 Window";

		WindowClass& operator=(const WindowClass&) = delete;

		static WindowClass instance;
		HINSTANCE hInstance;
	};
public:
	Window(int width, int height, const char* name);
	Window(const Window&) = delete;
	~Window();

	Window& operator=(const Window&) = delete;
	void SetTitle(const std::string& title);
	static std::optional<int> ProcessMessages();
private:
	static LRESULT CALLBACK HandleMessageSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	static LRESULT CALLBACK HandleMessageThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	LRESULT HandleMessages(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
public:
	Keyboard myKeyboard;
	Mouse myMouse;
private:
	int width;
	int height;
	HWND hWnd;
};