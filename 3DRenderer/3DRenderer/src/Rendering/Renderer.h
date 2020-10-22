#pragma once

#include "Core/WindowsDefines.h"
#include <d3d11.h>
#include <wrl.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

class Renderer
{
	friend class Bindable;

public:
	Renderer(HWND hWnd);
	~Renderer() = default;

	void endFrame();
	void clearBuffer(float r, float g, float b);
	void drawIndexed(uint32_t count);
	void setProjection(DirectX::FXMMATRIX proj);

	DirectX::XMMATRIX getProjection() const { return mProjection; }
	ID3D11Device* getDevice() { return mpDevice.Get(); }
	ID3D11DeviceContext* getContext() { return mpContext.Get(); }

private:
	DirectX::XMMATRIX mProjection;

	Microsoft::WRL::ComPtr<ID3D11Device> mpDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> mpContext;
	Microsoft::WRL::ComPtr<IDXGISwapChain> mpSwapChain;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> mpTarget;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> mpDepthStencilView;
};