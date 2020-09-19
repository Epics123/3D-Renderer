#pragma once

#include "Window.h"

class Application
{
public:
	Application();

	int start();

private:
	void update();

	Window mWindow;
};