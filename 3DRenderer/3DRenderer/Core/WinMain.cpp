#include "pch.h"
#include "WindowsDefines.h"

#include "Window.h"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Window window(WindowProps("DirectX 3D Renderer"));

	MSG msg;
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		if (window.getKeyboard().isKeyPressed(VK_SPACE))
			MessageBox(nullptr, L"Something Happened!", L"Space Key Was Pressed!", 0);
	}

	return msg.wParam;
}