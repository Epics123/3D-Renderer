#include "pch.h"
#include "TransformConstantBuffer.h"

TransformConstantBuffer::TransformConstantBuffer(Renderer& renderer, const Drawable& parent)
	:mVertexConstantBuff(renderer), mParent(parent)
{
	
}

void TransformConstantBuffer::bind(Renderer& renderer)
{
	mVertexConstantBuff.update(renderer, DirectX::XMMatrixTranspose(mParent.getTransform() * renderer.getProjection()));
	mVertexConstantBuff.bind(renderer);
}
