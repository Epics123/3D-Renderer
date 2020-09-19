#include "pch.h"
#include "Application.h"

Application::Application()
	:mWindow(WindowProps("3D Renderer"))
{
}

int Application::start()
{
	while (true)
	{
		if (const auto ecode = Window::processMessages())
			return *ecode;
		update();
	}
}

void Application::update()
{

}
