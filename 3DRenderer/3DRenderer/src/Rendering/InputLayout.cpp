#include "pch.h"
#include "InputLayout.h"

InputLayout::InputLayout(Renderer& renderer, const std::vector<D3D11_INPUT_ELEMENT_DESC>& layout, ID3DBlob* pVertexShaderBytecode)
{
	getDevice(renderer)->CreateInputLayout(layout.data(), uint32_t(layout.size()), pVertexShaderBytecode->GetBufferPointer(), pVertexShaderBytecode->GetBufferSize(), &mpInputLayout);
}

void InputLayout::bind(Renderer& renderer)
{
	getContext(renderer)->IASetInputLayout(mpInputLayout.Get());
}
