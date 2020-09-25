#pragma once

#include "WindowsDefines.h"
#include "3DRenderer.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Rendering/Graphics.h"

#include <optional>

struct WindowProps
{
	std::string Title;
	uint32_t Width;
	uint32_t Height;

	WindowProps(const std::string& title = "3D Renderer", uint32_t width = 1280, uint32_t height = 720)
		:Title(title), Width(width), Height(height){}
};

class Window
{
public:
	Window(const WindowProps& props);
	~Window();

	void onUpdate();

	uint32_t getWidth() const { return mData.Width; }
	uint32_t getHight() const { return mData.Height; }

	void setVsync(bool enabled);
	bool isVsync() const { return mData.vSync; }

	Keyboard& getKeyboard() { return mKeyboard; }
	Mouse& getMouse() { return mMouse; }
	Graphics& getGraphics() { return *mpGraphics; }

	void setTitle(const std::string& title);

	static std::optional<int> processMessages();

private:
	void init(const WindowProps& props);
	void shutdown();

	static LRESULT CALLBACK handleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK handleMsgThonk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT handleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
	struct WindowClass
	{
	public:
		static LPCTSTR getName();
		static HINSTANCE getInstance();

	private:
		WindowClass();
		~WindowClass();

		static constexpr LPCTSTR WindowClassName = L"Direct 3D Engine Window";
		static WindowClass WndClass;
		HINSTANCE HInst;
	};

	struct WindowData
	{
		std::string Title;
		uint32_t Width;
		uint32_t Height;
		bool vSync;
	};

	WindowData mData;
	HWND mHwnd;
	Keyboard mKeyboard;
	Mouse mMouse;
	Scope<Graphics> mpGraphics;
};