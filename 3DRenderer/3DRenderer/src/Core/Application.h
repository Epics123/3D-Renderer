#pragma once

#include "Window.h"
#include "Util/Timer.h"

class Application
{
public:
	Application();
	~Application() { mRunning = false; }

	int start();

private:
	void update();

	Window mWindow;
	Timer mTimer;

	bool mRunning;
};