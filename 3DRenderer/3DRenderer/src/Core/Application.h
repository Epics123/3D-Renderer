#pragma once

#include "Window.h"
#include "Util/Timer.h"

class Application
{
public:
	Application();

	int start();

private:
	void update();

	Window mWindow;
	Timer mTimer;
};