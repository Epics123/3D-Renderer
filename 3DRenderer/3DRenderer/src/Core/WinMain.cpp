#include "pch.h"
#include "WindowsDefines.h"

#include "Application.h"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Application app = Application();
	return app.start();
}