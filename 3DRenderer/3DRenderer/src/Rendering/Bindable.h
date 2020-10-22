#pragma once

#include "Renderer.h"

class Bindable
{
public:
	virtual ~Bindable() = default;

	virtual void bind(Renderer& renderer) = 0;
	virtual void unbind() = 0;

protected:
	static ID3D11DeviceContext* getContext(Renderer& renderer) { return renderer.mpContext.Get(); }
	static ID3D11Device* getDevice(Renderer& renderer) { return renderer.mpDevice.Get(); }
};