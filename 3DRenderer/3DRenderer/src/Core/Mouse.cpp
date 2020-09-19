#include "pch.h"
#include "Mouse.h"

#include "WindowsDefines.h"

Mouse::Event Mouse::read()
{
	if (mBuffer.size() > 0)
	{
		Mouse::Event e = mBuffer.front();
		mBuffer.pop();
		return e;
	}
	else
	{
		return Mouse::Event();
	}
}

void Mouse::flush()
{
	mBuffer = std::queue<Event>();
}

void Mouse::onMouseMove(Vector2D loc)
{
	mLocation = loc;

	mBuffer.push(Mouse::Event(Event::EventType::MouseMove, *this));
	trimBuffer();
}

void Mouse::onLeftPressed()
{
	mLeftPressed = true;

	mBuffer.push(Mouse::Event(Event::EventType::LeftPress, *this));
	trimBuffer();
}

void Mouse::onLeftReleased()
{
	mLeftPressed = false;

	mBuffer.push(Mouse::Event(Event::EventType::LeftRelease, *this));
	trimBuffer();
}

void Mouse::onRightPressed()
{
	mRightPressed = true;

	mBuffer.push(Mouse::Event(Event::EventType::RightPress, *this));
	trimBuffer();
}

void Mouse::onRightReleased()
{
	mLeftPressed = false;

	mBuffer.push(Mouse::Event(Event::EventType::RightRelease, *this));
	trimBuffer();
}

void Mouse::onScrollUp()
{
	mBuffer.push(Mouse::Event(Event::EventType::ScrollUp, *this));
	trimBuffer();
}

void Mouse::onScrollDown()
{
	mBuffer.push(Mouse::Event(Event::EventType::ScrollDown, *this));
	trimBuffer();
}

void Mouse::onMouseEnter()
{
	mInWindow = true;

	mBuffer.push(Mouse::Event(Event::EventType::Enter, *this));
	trimBuffer();
}

void Mouse::onMouseLeave()
{
	mInWindow = false;

	mBuffer.push(Mouse::Event(Event::EventType::Leave, *this));
	trimBuffer();
}

void Mouse::onWheelDelta(int delta)
{
	mWheelDeltaCarry += delta;
	while (mWheelDeltaCarry >= WHEEL_DELTA)
	{
		mWheelDeltaCarry -= WHEEL_DELTA;
		onScrollUp();
	}
	while (mWheelDeltaCarry <= -WHEEL_DELTA)
	{
		mWheelDeltaCarry += WHEEL_DELTA;
		onScrollDown();
	}
}

void Mouse::trimBuffer()
{
	while (mBuffer.size() > sBufferSize)
	{
		mBuffer.pop();
	}
}
