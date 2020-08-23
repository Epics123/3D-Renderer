#include "pch.h"

#include "Window.h"


Window::Window(const WindowProps& props)
{
	init(props);
}

Window::~Window()
{
	shutdown();
}

void Window::init(const WindowProps& props)
{
	mData.Title = props.Title;
	mData.Width = props.Width;
	mData.Height = props.Height;
}

void Window::shutdown()
{

}

void Window::onUpdate()
{

}

void Window::setVsync(bool enabled)
{

}
