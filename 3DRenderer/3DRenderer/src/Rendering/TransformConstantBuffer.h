#pragma once

#include "Buffer.h"
#include "Drawable.h"
#include <DirectXMath.h>

class TransformConstantBuffer : public Bindable
{
public:
	TransformConstantBuffer(Renderer& renderer, const Drawable& parent);
	virtual void bind(Renderer& renderer) override;
	virtual void unbind() override {}

private:
	VertexConstantBuffer<DirectX::XMMATRIX> mVertexConstantBuff;
	const Drawable& mParent;
};