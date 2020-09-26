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
	const float c = sin(mTimer.peek()) / 2.0f + 0.5f;

	mWindow.getGraphics().clearBuffer(0.0f, 0.0f, 0.0f);
	mWindow.getGraphics().draw(mTimer.peek());
	mWindow.getGraphics().endFrame();
}
