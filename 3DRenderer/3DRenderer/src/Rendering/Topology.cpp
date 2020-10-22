#include "pch.h"
#include "Topology.h"

Topology::Topology(Renderer& renderer, D3D11_PRIMITIVE_TOPOLOGY type)
	:mType(type)
{
}

void Topology::bind(Renderer& renderer)
{
	getContext(renderer)->IASetPrimitiveTopology(mType);
}
