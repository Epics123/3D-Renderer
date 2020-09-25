#pragma once
#include "Core/WindowsDefines.h"
#include <d3d11.h>
#include <wrl.h>

class Graphics
{
public:
	Graphics(HWND hWnd);
	~Graphics();

	void endFrame();
	void clearBuffer(float r, float g, float b, float a=1.0f);

	void draw();

private:
	Microsoft::WRL::ComPtr<ID3D11Device> mpDevice;
	Microsoft::WRL::ComPtr<IDXGISwapChain> mpSwapChain;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> mpContext;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> mpTarget;
};