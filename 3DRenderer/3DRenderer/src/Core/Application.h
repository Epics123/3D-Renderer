#pragma once

#include "3DRenderer.h"
#include "Window.h"
#include "Util/Timer.h"
#include "DrawableObjects/Cube.h"

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

	int mMaxObjects = 10;

	std::vector<Scope<Cube>> mCubes;
};