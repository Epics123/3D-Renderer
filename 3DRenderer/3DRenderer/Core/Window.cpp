#include "pch.h"
#include "Window.h"

Window::WindowClass Window::WindowClass::WndClass;

Window::WindowClass::WindowClass()
	:HInst(GetModuleHandle(nullptr))
{
	WNDCLASSEX windowClass = { 0 };
	windowClass.cbSize = sizeof(windowClass);
	windowClass.style = CS_OWNDC;
	windowClass.lpfnWndProc = handleMsgSetup;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = HInst;
	windowClass.hIcon = nullptr;
	windowClass.hCursor = nullptr;
	windowClass.hbrBackground = nullptr;
	windowClass.lpszMenuName = nullptr;
	windowClass.lpszClassName = getName();
	windowClass.hIconSm = nullptr;
	RegisterClassEx(&windowClass);
}

Window::WindowClass::~WindowClass()
{
	UnregisterClass(LPCTSTR(WindowClassName), getInstance());
}

LPCTSTR Window::WindowClass::getName()
{
	return WindowClassName;
}

HINSTANCE Window::WindowClass::getInstance()
{
	return WndClass.HInst;
}




Window::Window(const WindowProps& props)
{
	init(props);
}

Window::~Window()
{
	shutdown();
}

void Window::onUpdate()
{

}

void Window::setVsync(bool enabled)
{

}

void Window::init(const WindowProps& props)
{
	mData.Title = props.Title;
	mData.Width = props.Width;
	mData.Height = props.Height;

	RECT windowRec;
	windowRec.left = 100;
	windowRec.right = mData.Width + windowRec.left;
	windowRec.top = 100;
	windowRec.bottom = mData.Height + windowRec.top;
	AdjustWindowRect(&windowRec, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);

	std::wstring name;
	name.assign(mData.Title.begin(), mData.Title.end());
	LPCTSTR title = name.c_str();

	mHwnd = CreateWindow(WindowClass::getName(), title, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT,
		windowRec.right - windowRec.left, windowRec.bottom - windowRec.top, nullptr, nullptr, WindowClass::getInstance(), this);

	ShowWindow(mHwnd, SW_SHOWDEFAULT);
}

void Window::shutdown()
{
	
}

LRESULT CALLBACK Window::handleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_NCCREATE)
	{
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		Window* const pWindow = static_cast<Window*>(pCreate->lpCreateParams);
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWindow));
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::handleMsgThonk));

		return pWindow->handleMsg(hWnd, msg, wParam, lParam);
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT CALLBACK Window::handleMsgThonk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	Window* const pWindow = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	return pWindow->handleMsg(hWnd, msg, wParam, lParam);
}

LRESULT Window::handleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
	{
		PostQuitMessage(0);
		return 0;
	}break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}