#pragma once
#include "Rendering/Drawable.h"

#include <random>

typedef std::uniform_real_distribution<float> distribution;

class Cube : public Drawable
{
public:
	Cube(Renderer& renderer, std::mt19937& rng, distribution& alignmentDist, distribution& deltaDist, distribution& orientationDist, distribution& radiusDist);

	virtual void update(float dt) override;
	virtual DirectX::XMMATRIX getTransform() const override;

private:
	void init(Renderer& renderer);

	float mRadiusFromWorldOrigin;

	//Positional values
	float mRoll = 0.0f;
	float mPitch = 0.0f;
	float mYaw = 0.0f;
	float mTheta;
	float mPhi;
	float mChi;

	//Speed values
	float mRollSpeed;
	float mPitchSpeed;
	float mYawSpeed;
	float mThetaDelta;
	float mPhiDelta;
	float mChiDelta;
};