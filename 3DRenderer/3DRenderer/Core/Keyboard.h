#pragma once

#include <queue>
#include <bitset>

class Keyboard
{
	friend class Window;
public:
	class Event
	{
	public:
		enum class EventType
		{
			Press,
			Release,
			Invalid
		};

	private:
		EventType mType;
		uint32_t mKeyCode;

	public:
		Event()
			:mType(EventType::Invalid), mKeyCode(0) {}

		Event(EventType type, uint32_t keyCode)
			:mType(type), mKeyCode(keyCode) {}

		bool isPressed() const { return mType == EventType::Press; }
		bool isReleased() const { return mType == EventType::Release; }
		bool isValid() const { return mType != EventType::Invalid; }

		uint32_t getKeyCode() const { return mKeyCode; }
	};

public:
	Keyboard() = default;

	bool isKeyPressed(uint32_t keyCode) const;
	Event readKey();
	bool isKeyEmpty() const;
	void flushKey();

	char readChar();
	bool isCharEmpty() const;
	void flushChar();
	void flush();

	void enableAutoRepeat();
	void disableAutoRepeat();
	bool autoRepeatEnabled() const;

private:
	void onKeyPressed(uint32_t keyCode);
	void onKeyReleased(uint32_t keyCode);
	void onChar(char character);
	void clearState();

	template<typename T>
	static void trimBuffer(std::queue<T>& buffer);

private:
	static constexpr uint32_t mNumKeys = 256;
	static constexpr uint32_t mBufferSize = 16;

	bool mAutoRepeat = false;

	std::bitset<mNumKeys> mKeyStates;
	std::queue<Event> mKeyBuffer;
	std::queue<char> mCharBuffer;
};
