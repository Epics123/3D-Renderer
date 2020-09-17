#pragma once
#include <cfloat>

class Vector2D
{
public:
	Vector2D();
	Vector2D(int x, int y);
	Vector2D(float x = 0.0f, float y = 0.0f);
	Vector2D(const Vector2D& rhs);
	~Vector2D() = default;

	Vector2D& operator += (const Vector2D& rhs);
	Vector2D& operator -= (const Vector2D& rhs);
	Vector2D& operator *= (float mult);
	Vector2D& operator /= (float div);
	Vector2D& operator = (const Vector2D& rhs);

	bool operator == (const Vector2D& rhs)const;
	bool operator != (const Vector2D& rhs)const;

	Vector2D operator+(const Vector2D& other) const;
	Vector2D operator-(const Vector2D& other) const;
	Vector2D operator*(float mult) const;
	Vector2D operator/(float div) const;

	float getX() const { return mX; }
	float getY() const { return mY; }

	void setX(float x) { mX = x; }
	void setY(float y) { mY = y; }

	bool hasNonZeroLength() const;
	float getLength() const;
	float getLengthSquared() const;

	void normalize();
	Vector2D getNormalizedVector() const;

	float dot(const Vector2D& other) const;
	double calcFacing() const;

	Vector2D getRightVector() const;

private:
	float mX, mY;
};