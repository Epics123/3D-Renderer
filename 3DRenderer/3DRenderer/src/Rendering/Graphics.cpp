#include "pch.h"
#include "Graphics.h"

#include <d3dcompiler.h>
#include <DirectXMath.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")

namespace wrl = Microsoft::WRL;
namespace dx = DirectX;

Graphics::Graphics(HWND hWnd)
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
}

Graphics::~Graphics()
{
}

void Graphics::endFrame()
{
	mpSwapChain->Present(1, 0);
}

void Graphics::clearBuffer(float r, float g, float b, float a)
{
	const float color[] = { r, g, b, a };
	mpContext->ClearRenderTargetView(mpTarget.Get(), color);
	mpContext->ClearDepthStencilView(mpDepthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void Graphics::draw(float angle, float x, float z)
{
	struct Vertex 
	{ 
		struct
		{
			float x, y, z;
		} pos;
	};
	Vertex verticies[] =
	{
		{-1.0f, -1.0f, -1.0f},
		{1.0f, -1.0f, -1.0f},
		{-1.0f, 1.0f, -1.0f},
		{1.0f, 1.0f, -1.0f},
		{-1.0f, -1.0f, 1.0f},
		{1.0f, -1.0f, 1.0f},
		{-1.0f, 1.0f, 1.0f},
		{1.0f, 1.0f, 1.0f}
	};

	//Create Vertex Buffer
	wrl::ComPtr<ID3D11Buffer> pVertexBuffer;
	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.ByteWidth = sizeof(verticies);
	bufferDesc.StructureByteStride = sizeof(Vertex);
	D3D11_SUBRESOURCE_DATA sd = {};
	sd.pSysMem = verticies;

	mpDevice->CreateBuffer(&bufferDesc, &sd, &pVertexBuffer);

	//Bind Vertex Buffer to Pipeline
	const UINT stride = sizeof(Vertex);
	const UINT offset = 0;
	mpContext->IASetVertexBuffers(0, 1, pVertexBuffer.GetAddressOf(), &stride, &offset);

	//Create Index Buffer
	const unsigned short indicies[] =
	{
		0, 2, 1,  2, 3, 1,
		1, 3, 5,  3, 7, 5,
		2, 6, 3,  3, 6, 7,
		4, 5, 7,  4, 7, 6,
		0, 4, 2,  2, 4, 6,
		0, 1, 4,  1, 5, 4
	};
	wrl::ComPtr<ID3D11Buffer> pIndexBuffer;
	D3D11_BUFFER_DESC iBufferDesc = {};
	iBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	iBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	iBufferDesc.CPUAccessFlags = 0;
	iBufferDesc.MiscFlags = 0;
	iBufferDesc.ByteWidth = sizeof(indicies);
	iBufferDesc.StructureByteStride = sizeof(unsigned short);
	D3D11_SUBRESOURCE_DATA isd = {};
	isd.pSysMem = indicies;

	mpDevice->CreateBuffer(&iBufferDesc, &isd, &pIndexBuffer);

	//Bind Index Buffer to Pipeline
	mpContext->IASetIndexBuffer(pIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);

	//Create Constant Buffer for Transformation Matrix
	struct ConstantBuffer
	{
		struct
		{
			dx::XMMATRIX transform;
		}transformation;
	};

	const ConstantBuffer cb =
	{
		{
			dx::XMMatrixTranspose(dx::XMMatrixRotationZ(angle) * dx::XMMatrixRotationX(angle) *
			dx::XMMatrixTranslation(x, 0.0f, z + 4.0f) * dx::XMMatrixPerspectiveLH(1.0f, 9.0f/16.0f, 0.5f, 10.0f))
		}
	};

	wrl::ComPtr<ID3D11Buffer> pConstantBuffer;
	D3D11_BUFFER_DESC cBufferDesc;
	cBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	cBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cBufferDesc.MiscFlags = 0;
	cBufferDesc.ByteWidth = sizeof(cb);
	cBufferDesc.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA csd = {};
	csd.pSysMem = &cb;

	mpDevice->CreateBuffer(&cBufferDesc, &csd, &pConstantBuffer);

	//Bind Constant Buffer to Pipeline
	mpContext->VSSetConstantBuffers(0, 1, pConstantBuffer.GetAddressOf());

	struct ConstantBuffer2
	{
		struct
		{
			float r, g, b, a;
		}faceColors[6];
	};

	const ConstantBuffer2 cb2 =
	{
		{
			{1.0f,0.0f,1.0f},
			{1.0f,0.0f,0.0f},
			{0.0f,1.0f,0.0f},
			{0.0f,0.0f,1.0f},
			{1.0f,1.0f,0.0f},
			{0.0f,1.0f,1.0f},
		}
	};

	wrl::ComPtr<ID3D11Buffer> pConstantBuffer2;
	D3D11_BUFFER_DESC cbd2;
	cbd2.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd2.Usage = D3D11_USAGE_DEFAULT;
	cbd2.CPUAccessFlags = 0;
	cbd2.MiscFlags = 0;
	cbd2.ByteWidth = sizeof(cb2);
	cbd2.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA csd2 = {};
	csd2.pSysMem = &cb2;

	mpDevice->CreateBuffer(&cbd2, &csd2, &pConstantBuffer2);

	mpContext->PSSetConstantBuffers(0, 1, pConstantBuffer2.GetAddressOf());

	//Create Pixel Shader
	wrl::ComPtr<ID3D11PixelShader> pPixelShader;
	wrl::ComPtr<ID3DBlob> pBlob;
	D3DReadFileToBlob(L"PixelShader.cso", &pBlob);
	mpDevice->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPixelShader);

	mpContext->PSSetShader(pPixelShader.Get(), nullptr, 0);

	//Create Vertex Shader
	wrl::ComPtr<ID3D11VertexShader> pVertexShader;
	D3DReadFileToBlob(L"VertexShader.cso", &pBlob);
	mpDevice->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pVertexShader);

	mpContext->VSSetShader(pVertexShader.Get(), nullptr, 0);

	wrl::ComPtr<ID3D11InputLayout> pInputLayout;
	const D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	mpDevice->CreateInputLayout(ied, (UINT)std::size(ied), pBlob->GetBufferPointer(), pBlob->GetBufferSize(), &pInputLayout);

	mpContext->IASetInputLayout(pInputLayout.Get());

	mpContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//Configure Viewport
	D3D11_VIEWPORT vp;
	vp.Width = 1280;
	vp.Height = 720;
	vp.MinDepth = 0;
	vp.MaxDepth = 1;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	mpContext->RSSetViewports(1, &vp);

	mpContext->DrawIndexed((UINT)std::size(indicies), 0, 0);
}
