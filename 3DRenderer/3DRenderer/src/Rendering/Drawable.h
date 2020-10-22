#pragma once

#include "Bindable.h"
#include "Core/Core.h"
#include "Rendering/Buffer.h"
#include <DirectXMath.h>

class Drawable
{
public:
	Drawable() {};
	~Drawable() = default;

	virtual void update(float dt) = 0;
	virtual DirectX::XMMATRIX getTransform() const = 0;

	void draw(Renderer& renderer) const;
	void addBindable(Scope<Bindable> bind);
	void addIndexBuffer(Scope<IndexBuffer> buff);

private:
	const IndexBuffer* mpIndexBuffer = nullptr;
	std::vector<Scope<Bindable>> mBindables;
};