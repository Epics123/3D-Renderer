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
	mWindow.getGraphics().clearBuffer(0.0f, 0.0f, 0.0f);
	mWindow.getGraphics().draw(-mTimer.peek(), 0.0f, 0.0f);
	mWindow.getGraphics().draw(mTimer.peek(), mWindow.getMouse().getX() / 1280.0f - 1.0f, -mWindow.getMouse().getY() / 720.0f + 1.0f);
	mWindow.getGraphics().endFrame();
}
