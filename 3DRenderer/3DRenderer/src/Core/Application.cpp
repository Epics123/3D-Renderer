#include "pch.h"
#include "Application.h"

#define _USE_MATH_DEFINES
#include <math.h>

Application::Application()
	:mWindow(WindowProps("3D Renderer")), mRunning(true)
{
	std::mt19937 rng(std::random_device{}());
	std::uniform_real_distribution<float> alignmentDist(0.0f, (float)M_PI * 2.0f);
	std::uniform_real_distribution<float> deltaDist(0.0f, (float)M_PI * 2.0f);
	std::uniform_real_distribution<float> orientationDist(0.0f, (float)M_PI * 2.0f);
	std::uniform_real_distribution<float> radiusDist(6.0f, 20.0f);

	for (int i = 0; i < mMaxObjects; i++)
	{
		mCubes.push_back(CreateScope<Cube>(mWindow.getRenderer(), rng, alignmentDist, deltaDist, orientationDist, radiusDist));
	}
	DirectX::XMMATRIX proj = DirectX::XMMatrixPerspectiveLH(1.0f, 9.0f / 16.0f, 0.5f, 40.0f);
	mWindow.getRenderer().setProjection(proj);
}

int Application::start()
{
	while (mRunning)
	{
		if (const auto ecode = Window::processMessages())
			return *ecode;
		update();
	}
	return 0;
}

void Application::update()
{
	/*mWindow.getGraphics().clearBuffer(0.0f, 0.0f, 0.0f);
	mWindow.getGraphics().draw(-mTimer.peek(), 2.0f, 0.0f);
	mWindow.getGraphics().draw(mTimer.peek(), mWindow.getMouse().getX() / 1280.0f - 1.0f, -mWindow.getMouse().getY() / 720.0f + 1.0f);
	mWindow.getGraphics().endFrame();*/

	auto dt = mTimer.mark();

	mWindow.getRenderer().clearBuffer(0.0f, 0.0f, 0.0f);
	for (auto& cube : mCubes)
	{
		cube->update(dt);
		cube->draw(mWindow.getRenderer());
	}
	mWindow.getRenderer().endFrame();
}
