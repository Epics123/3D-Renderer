#pragma once

#include "pch.h"
#include "Application.h"

int main()
{
	auto app = new Application("3D-Renderer");

	app->run();

	system("pause");
	return 0;
}