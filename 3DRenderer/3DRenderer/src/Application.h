#pragma once

#include "Core.h"
#include "Window.h"

class Application
{
public:
	Application(const std::string& name = "App");
	virtual ~Application();

	void run();
	void close();

	Window& getWindow() { return *mWindow; }

	static Application& getInstance() { return *sInstance; }

private:
	static Application* sInstance;

	Scope<Window> mWindow;
	bool mRunning = true;
	bool mMinimized = false;
};