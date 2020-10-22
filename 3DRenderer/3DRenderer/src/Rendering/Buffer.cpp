#include "pch.h"
#include "Buffer.h"

IndexBuffer::IndexBuffer(Renderer& renderer, const std::vector<unsigned short>& indicies)
	:mCount((uint32_t)indicies.size())
{
	D3D11_BUFFER_DESC iBufferDesc = {};
	iBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	iBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	iBufferDesc.CPUAccessFlags = 0;
	iBufferDesc.MiscFlags = 0;
	iBufferDesc.ByteWidth = uint32_t(mCount * sizeof(unsigned short));
	iBufferDesc.StructureByteStride = sizeof(unsigned short);
	D3D11_SUBRESOURCE_DATA isd = {};
	isd.pSysMem = indicies.data();
	
	getDevice(renderer)->CreateBuffer(&iBufferDesc, &isd, &mpIndexBuffer);
}

IndexBuffer::~IndexBuffer()
{
}

void IndexBuffer::bind(Renderer& renderer)
{
	getContext(renderer)->IASetIndexBuffer(mpIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);
}

void IndexBuffer::unbind()
{
}

VertexBuffer::~VertexBuffer()
{
}

void VertexBuffer::bind(Renderer& renderer)
{
	uint32_t offset = 0;
	getContext(renderer)->IASetVertexBuffers(0, 1, mpVertexBuffer.GetAddressOf(), &mStride, &offset);
}

void VertexBuffer::unbind()
{
}
