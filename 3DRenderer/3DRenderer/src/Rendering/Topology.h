#pragma once

#include "Bindable.h"

class Topology : public Bindable
{
public:
	Topology(Renderer& renderer, D3D11_PRIMITIVE_TOPOLOGY type);

	virtual void bind(Renderer& renderer) override;
	virtual void unbind() override {}

protected:
	D3D11_PRIMITIVE_TOPOLOGY mType;
};