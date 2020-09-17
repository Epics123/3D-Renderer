#pragma once

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
			Invalid
		};

	private:
		EventType mType;
		bool mLeftPressed, mRightPressed;
		int mX, mY;

	public:
		Event()
			:mType(EventType::Invalid), mLeftPressed(false), mRightPressed(false), mX(0), mY(0)
		{
		}

		/*Event(EventType type, const Mouse& parent)
			:mType(type), mLeftPressed(parent.mLeftPressed), mRightPressed(parent.mRightPressed), mX(parent.mX), mY(parent.mY) {}*/

		bool isValid() const { return mType != EventType::Invalid; }
		EventType getType() const { return mType; }

	};
};