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

		while (!window.getMouse().isEmpty())
		{
			const auto e = window.getMouse().read();

			switch (e.getType())
			{
			case Mouse::Event::EventType::Leave:
				window.setTitle("Gone!");
				break;
			case Mouse::Event::EventType::MouseMove:
				{
					std::ostringstream oss;
					oss << "Mouse Position: (" << e.getX() << ", " << e.getY() << ")";
					window.setTitle(oss.str());
				}
				break;
			}
		}
	}

	return msg.wParam;
}