#include "pch.h"
#include "Shader.h"

PixelShader::PixelShader(Renderer& renderer, const std::wstring& path)
{
	Microsoft::WRL::ComPtr<ID3DBlob> pBlob;
	D3DReadFileToBlob(path.c_str(), &pBlob);
	getDevice(renderer)->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &mpPixelShader);
}

void PixelShader::bind(Renderer& renderer)
{
	getContext(renderer)->PSSetShader(mpPixelShader.Get(), nullptr, 0);
}

VertexShader::VertexShader(Renderer& renderer, const std::wstring& path)
{
	D3DReadFileToBlob(path.c_str(), &mpBytecodeBlob);
	getDevice(renderer)->CreateVertexShader(mpBytecodeBlob->GetBufferPointer(), mpBytecodeBlob->GetBufferSize(), nullptr, &mpVertexShader);
}

void VertexShader::bind(Renderer& renderer)
{
	getContext(renderer)->VSSetShader(mpVertexShader.Get(), nullptr, 0);
}
