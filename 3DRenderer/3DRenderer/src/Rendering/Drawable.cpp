#include "pch.h"
#include "Drawable.h"

#include <cassert>

void Drawable::draw(Renderer& renderer) const
{
	for (auto& bind : mBindables)
	{
		bind->bind(renderer);
	}
	renderer.drawIndexed(mpIndexBuffer->getCount());
}

void Drawable::addBindable(Scope<Bindable> bind)
{
	assert("Must use addIndexBuffer to bind IndexBuffer" && typeid(*bind) != typeid(IndexBuffer)); //Make sure addIndexBuffer is used to add IndexBuffers
	mBindables.push_back(std::move(bind));
}

void Drawable::addIndexBuffer(Scope<IndexBuffer> buff)
{
	assert("IndexBuffer already exists!" && mpIndexBuffer == nullptr);
	mpIndexBuffer = buff.get();
	mBindables.push_back(std::move(buff));
}
