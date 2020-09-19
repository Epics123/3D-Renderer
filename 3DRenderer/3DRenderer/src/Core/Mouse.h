#pragma once

#include "Util/Vector2D.h"

#include <queue>

class Mouse
{
	friend class Window;

public:
	class Event
	{
	public:
		enum class EventType
		{
			LeftPress,
			LeftRelease,
			RightPress,
			RightRelease,
			ScrollUp,
			ScrollDown,
			MouseMove,
			Enter,
			Leave,
			Invalid
		};

	private:
		EventType mType;
		bool mLeftPressed, mRightPressed;
		Vector2D mLocation;

	public:
		Event()
			:mType(EventType::Invalid), mLeftPressed(false), mRightPressed(false), mLocation(0.0f, 0.0f)
		{
		}

		Event(EventType type, const Mouse& parent)
			:mType(type), mLeftPressed(parent.mLeftPressed), mRightPressed(parent.mRightPressed), mLocation(parent.mLocation) {}

		bool isValid() const { return mType != EventType::Invalid; }
		EventType getType() const { return mType; }

		Vector2D getPos() const { return mLocation; }
		float getX() const { return mLocation.getX(); }
		float getY() const { return mLocation.getY(); }

		bool isLeftPressed() const { return mLeftPressed; }
		bool isRightPressed() const { return mRightPressed; }
	};

public:
	Mouse() = default;

	Vector2D getPos() const { return mLocation; }
	int getX() const { return mLocation.getX(); }
	int getY() const { return mLocation.getY(); }

	bool isLeftPressed() const { return mLeftPressed; }
	bool isRightPressed() const { return mRightPressed; }
	bool isInWindow() const { return mInWindow; }

	Mouse::Event read();

	bool isEmpty() const { return mBuffer.empty(); }
	void flush();

private:
	void onMouseMove(Vector2D loc);
	void onLeftPressed();
	void onLeftReleased();
	void onRightPressed();
	void onRightReleased();
	void onScrollUp();
	void onScrollDown();
	void onMouseEnter();
	void onMouseLeave();
	void onWheelDelta(int delta);

	void trimBuffer();

	static constexpr uint32_t sBufferSize = 16;

	Vector2D mLocation;
	bool mLeftPressed = false;
	bool mRightPressed = false;
	bool mInWindow = false;
	int mWheelDeltaCarry = 0;
	std::queue<Event> mBuffer;
};