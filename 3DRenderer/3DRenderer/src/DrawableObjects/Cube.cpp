#include "pch.h"
#include "Cube.h"

#include "Rendering/Buffer.h"
#include "Rendering/Shader.h"
#include "Rendering/InputLayout.h"
#include "Rendering/Topology.h"
#include "Rendering/TransformConstantBuffer.h"

Cube::Cube(Renderer& renderer, std::mt19937& rng, distribution& alignmentDist, distribution& deltaDist, distribution& orientationDist, distribution& radiusDist)
	:mTheta(alignmentDist(rng)), mPhi(alignmentDist(rng)), mChi(alignmentDist(rng)), mRollSpeed(deltaDist(rng)), mPitchSpeed(deltaDist(rng)), mYawSpeed(deltaDist(rng)),
	mThetaDelta(orientationDist(rng)), mPhiDelta(orientationDist(rng)), mChiDelta(orientationDist(rng)), mRadiusFromWorldOrigin(radiusDist(rng))
{
	init(renderer);
}

void Cube::init(Renderer& renderer)
{

	//Create and Verticies
	struct Vertex
	{
		struct
		{
			float x, y, z;
		}pos;
	};

	const std::vector<Vertex> verticies =
	{
		{-1.0f, -1.0f, -1.0f},
		{1.0f, -1.0f, -1.0f},
		{-1.0f, 1.0f, -1.0f},
		{1.0f, 1.0f, -1.0f},
		{-1.0f, -1.0f, 1.0f},
		{1.0f, -1.0f, 1.0f},
		{-1.0f, 1.0f, 1.0f},
		{1.0f, 1.0f, 1.0f}
	};
	addBindable(CreateScope<VertexBuffer>(renderer, verticies));

	//Create and Bind Vertex Shader
	auto pVertexShader = CreateScope<VertexShader>(renderer, L"VertexShader.cso");
	auto pVertexShaderByteCode = pVertexShader->getBytecode();
	addBindable(std::move(pVertexShader));

	//Crate and Pixel Shader
	addBindable(CreateScope<PixelShader>(renderer, L"PixelShader.cso"));

	//Create Index Buffer
	const std::vector<unsigned short> indicies =
	{
		0, 2, 1,  2, 3, 1,
		1, 3, 5,  3, 7, 5,
		2, 6, 3,  3, 6, 7,
		4, 5, 7,  4, 7, 6,
		0, 4, 2,  2, 4, 6,
		0, 1, 4,  1, 5, 4
	};
	addIndexBuffer(CreateScope<IndexBuffer>(renderer, indicies));

	struct ColorBuffer
	{
		struct
		{
			float r, g, b, a;
		}faceColors[6];
	};

	const ColorBuffer colBuffer =
	{
		{
			{1.0f,0.0f,1.0f},
			{1.0f,0.0f,0.0f},
			{0.0f,1.0f,0.0f},
			{0.0f,0.0f,1.0f},
			{1.0f,1.0f,0.0f},
			{0.0f,1.0f,1.0f},
		}
	};
	addBindable(CreateScope<PixelConstantBuffer<ColorBuffer>>(renderer, colBuffer));

	const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
	{
		{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	addBindable(CreateScope<InputLayout>(renderer, ied, pVertexShaderByteCode));

	addBindable(CreateScope<Topology>(renderer, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

	addBindable(CreateScope<TransformConstantBuffer>(renderer, *this));
}

void Cube::update(float dt)
{
	mRoll += mRollSpeed * dt / 4.0f;
	mPitch += mPitchSpeed * dt / 4.0f;
	mYaw += mYawSpeed * dt / 4.0f;

	mTheta += mThetaDelta * dt / 4.0f;
	mPhi += mPhiDelta * dt / 4.0f;
	mChi += mChiDelta * dt / 4.0f;
}

DirectX::XMMATRIX Cube::getTransform() const
{
	return DirectX::XMMatrixRotationRollPitchYaw(mPitch, mYaw, mRoll) * DirectX::XMMatrixTranslation(mRadiusFromWorldOrigin, 0.0f, 0.0f) *
		   DirectX::XMMatrixRotationRollPitchYaw(mTheta, mPhi, mChi) * DirectX::XMMatrixTranslation(0.0f, 0.0f, 20.0f);
}
