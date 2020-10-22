#include "pch.h"
#include "Renderer.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")

namespace wrl = Microsoft::WRL;
namespace dx = DirectX;

Renderer::Renderer(HWND hWnd)
{
	DXGI_SWAP_CHAIN_DESC swapDesc = {};
	swapDesc.BufferDesc.Width = 0;
	swapDesc.BufferDesc.Height = 0;
	swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapDesc.BufferDesc.RefreshRate.Numerator = 0;
	swapDesc.BufferDesc.RefreshRate.Denominator = 0;
	swapDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapDesc.SampleDesc.Count = 1;
	swapDesc.SampleDesc.Quality = 0;
	swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapDesc.BufferCount = 1;
	swapDesc.OutputWindow = hWnd;
	swapDesc.Windowed = true;
	swapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapDesc.Flags = 0;

	D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION, &swapDesc, &mpSwapChain, &mpDevice, nullptr, &mpContext);

	wrl::ComPtr<ID3D11Resource> pBackBuffer = nullptr;
	mpSwapChain->GetBuffer(0, __uuidof(ID3D11Resource), &pBackBuffer);
	mpDevice->CreateRenderTargetView(pBackBuffer.Get(), nullptr, &mpTarget);

	pBackBuffer->Release();

	//Create Depth Stencil State
	D3D11_DEPTH_STENCIL_DESC dsDesc = {};
	dsDesc.DepthEnable = TRUE;
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS;
	wrl::ComPtr<ID3D11DepthStencilState> pDSState;

	mpDevice->CreateDepthStencilState(&dsDesc, &pDSState);

	//Bind Depth State
	mpContext->OMSetDepthStencilState(pDSState.Get(), 1);

	//Create Depth Stencil Texture
	wrl::ComPtr<ID3D11Texture2D> pDepthStencil;
	D3D11_TEXTURE2D_DESC depthDesc = {};
	depthDesc.Width = 1280;
	depthDesc.Height = 720;
	depthDesc.MipLevels = 1;
	depthDesc.ArraySize = 1;
	depthDesc.Format = DXGI_FORMAT_D32_FLOAT;
	depthDesc.SampleDesc.Count = 1;
	depthDesc.SampleDesc.Quality = 0;
	depthDesc.Usage = D3D11_USAGE_DEFAULT;
	depthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

	mpDevice->CreateTexture2D(&depthDesc, nullptr, &pDepthStencil);

	//Create View of Depth Stencil Texture
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;
	dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvDesc.Texture2D.MipSlice = 0;

	mpDevice->CreateDepthStencilView(pDepthStencil.Get(), &dsvDesc, &mpDepthStencilView);

	//Bind Depth Stencil View
	mpContext->OMSetRenderTargets(1, mpTarget.GetAddressOf(), mpDepthStencilView.Get());

	//Configure Viewport
	D3D11_VIEWPORT vp;
	vp.Width = 1280;
	vp.Height = 720;
	vp.MinDepth = 0;
	vp.MaxDepth = 1;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	mpContext->RSSetViewports(1, &vp);
}

void Renderer::endFrame()
{
	mpSwapChain->Present(1, 0);
}

void Renderer::clearBuffer(float r, float g, float b)
{
	const float color[] = { r, g, b, 1.0f };
	mpContext->ClearRenderTargetView(mpTarget.Get(), color);
	mpContext->ClearDepthStencilView(mpDepthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void Renderer::drawIndexed(uint32_t count)
{
	mpContext->DrawIndexed(count, 0, 0);
}

void Renderer::setProjection(DirectX::FXMMATRIX proj)
{
	mProjection = proj;
}
