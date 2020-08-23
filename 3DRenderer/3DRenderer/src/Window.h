#pragma once

#include "Core.h"

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

	void init(const WindowProps& props);
	void shutdown();

	void onUpdate();

	uint32_t getWidth() const { return mData.Width; }
	uint32_t getHeight() const { return mData.Height; }

	void setVsync(bool enabled);
	bool isVsync() const { return mData.vSync; }

private:

	struct WindowData
	{
		std::string Title;
		uint32_t Width;
		uint32_t Height;
		bool vSync;
	};

	WindowData mData;
};