#pragma once

#include "Bindable.h"

class InputLayout : public Bindable
{
public:
	InputLayout(Renderer& renderer, const std::vector<D3D11_INPUT_ELEMENT_DESC>& layout, ID3DBlob* pVertexShaderBytecode);

	virtual void bind(Renderer& renderer) override;
	virtual void unbind() override {}

protected:
	Microsoft::WRL::ComPtr<ID3D11InputLayout> mpInputLayout;
};