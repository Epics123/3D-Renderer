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

	void draw(float angle, float x, float z);

	ID3D11DeviceContext* getContext() { return mpContext.Get(); }
	ID3D11Device* getDevice() { return mpDevice.Get(); }

private:
	Microsoft::WRL::ComPtr<ID3D11Device> mpDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> mpContext;
	Microsoft::WRL::ComPtr<IDXGISwapChain> mpSwapChain;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> mpTarget;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> mpDepthStencilView;
};