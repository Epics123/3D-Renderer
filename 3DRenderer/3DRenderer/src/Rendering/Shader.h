#pragma once

#include "Bindable.h"

class PixelShader : public Bindable
{
public:
	PixelShader(Renderer& renderer, const std::wstring& path);

	virtual void bind(Renderer& renderer) override;
	virtual void unbind() override {}

protected:
	Microsoft::WRL::ComPtr<ID3D11PixelShader> mpPixelShader;
};

class VertexShader : public Bindable
{
public:
	VertexShader(Renderer& renderer, const std::wstring& path);

	virtual void bind(Renderer& renderer) override;
	virtual void unbind() override {}
	ID3DBlob* getBytecode() const { return mpBytecodeBlob.Get(); }

protected:
	Microsoft::WRL::ComPtr<ID3D11VertexShader> mpVertexShader;
	Microsoft::WRL::ComPtr<ID3DBlob> mpBytecodeBlob;
};