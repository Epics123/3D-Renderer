#include "pch.h"

#include "Application.h"

Application* Application::sInstance = nullptr;

Application::Application(const std::string& name)
{
	sInstance = this;

	mWindow = CreateScope<Window>(WindowProps(name));
}

Application::~Application()
{

}

void Application::run()
{
	while (mRunning)
	{

	}
}

void Application::close()
{
	mRunning = false;
}
