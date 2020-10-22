#pragma once

#include <vector>
#include <wrl.h>

#include "Bindable.h"

class IndexBuffer : public Bindable
{
public:
	IndexBuffer(Renderer& renderer, const std::vector<unsigned short>& indicies);
	~IndexBuffer();

	virtual void bind(Renderer& renderer) override;
	virtual void unbind() override;

	uint32_t getCount() const { return mCount; }

protected:
	Microsoft::WRL::ComPtr<ID3D11Buffer> mpIndexBuffer;

private:
	uint32_t mCount;
};


class VertexBuffer : public Bindable
{
public:
	template<class T>
	VertexBuffer(Renderer& renderer, const std::vector<T>& verticies)
		:mStride(sizeof(T))
	{
		D3D11_BUFFER_DESC bufferDesc = {};
		bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		bufferDesc.CPUAccessFlags = 0;
		bufferDesc.MiscFlags = 0;
		bufferDesc.ByteWidth = UINT(sizeof(T) * verticies.size());
		bufferDesc.StructureByteStride = sizeof(T);
		D3D11_SUBRESOURCE_DATA sd = {};
		sd.pSysMem = verticies.data();

		HRESULT res = getDevice(renderer)->CreateBuffer(&bufferDesc, &sd, &mpVertexBuffer);
	}

	~VertexBuffer();

	virtual void bind(Renderer& renderer) override;
	virtual void unbind() override;

	uint32_t getSride() const { return mStride; }

protected:
	uint32_t mStride;
	Microsoft::WRL::ComPtr<ID3D11Buffer> mpVertexBuffer;
};

template<typename C>
class ConstantBuffer : public Bindable
{
public:
	ConstantBuffer(Renderer& renderer, const C& constBuffs)
	{
		D3D11_BUFFER_DESC cBufferDesc;
		cBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		cBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cBufferDesc.MiscFlags = 0;
		cBufferDesc.ByteWidth = sizeof(constBuffs);
		cBufferDesc.StructureByteStride = 0;
		D3D11_SUBRESOURCE_DATA csd = {};
		csd.pSysMem = &constBuffs;

		renderer.getDevice()->CreateBuffer(&cBufferDesc, &csd, &mpConstantBuffer);

	}

	ConstantBuffer(Renderer& renderer)
	{
		D3D11_BUFFER_DESC cBufferDesc;
		cBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		cBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cBufferDesc.MiscFlags = 0;
		cBufferDesc.ByteWidth = sizeof(C);
		cBufferDesc.StructureByteStride = 0;

		renderer.getDevice()->CreateBuffer(&cBufferDesc, nullptr, &mpConstantBuffer);
	}

	void update(Renderer& renderer, const C& constBuffs)
	{
		D3D11_MAPPED_SUBRESOURCE msr;
		renderer.getContext()->Map(mpConstantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
		memcpy(msr.pData, &constBuffs, sizeof(constBuffs));
		renderer.getContext()->Unmap(mpConstantBuffer.Get(), 0);
	}

protected:
	Microsoft::WRL::ComPtr<ID3D11Buffer> mpConstantBuffer;
};

template<typename C>
class VertexConstantBuffer : public ConstantBuffer<C>
{
public:
	VertexConstantBuffer(Renderer& renderer, const C& constBuffs)
		:ConstantBuffer(renderer, constBuffs)
	{
	}

	VertexConstantBuffer(Renderer& renderer)
		:ConstantBuffer(renderer)
	{
	}

	virtual void bind(Renderer& renderer) override
	{
		renderer.getContext()->VSSetConstantBuffers(0, 1, mpConstantBuffer.GetAddressOf());
	}

	virtual void unbind() override {}
};

template<typename C>
class PixelConstantBuffer : public ConstantBuffer<C>
{
public:
	PixelConstantBuffer(Renderer& renderer, const C& constBuffs)
		:ConstantBuffer(renderer, constBuffs)
	{
	}

	PixelConstantBuffer(Renderer& renderer)
		:ConstantBuffer(renderer)
	{
	}

	virtual void bind(Renderer& renderer) override
	{
		renderer.getContext()->PSSetConstantBuffers(0, 1, mpConstantBuffer.GetAddressOf());
	}

	virtual void unbind() override {}
};