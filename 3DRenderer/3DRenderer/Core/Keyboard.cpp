#include "pch.h"
#include "Keyboard.h"

bool Keyboard::isKeyPressed(uint32_t keyCode) const
{
	return mKeyStates[keyCode];
}

Keyboard::Event Keyboard::readKey()
{
	if (mKeyBuffer.size() > 0)
	{
		Keyboard::Event e = mKeyBuffer.front();
		mKeyBuffer.pop();
		return e;
	}
	else
	{
		return Keyboard::Event();
	}
}

bool Keyboard::isKeyEmpty() const
{
	return mKeyBuffer.empty();
}

char Keyboard::readChar()
{
	if (mCharBuffer.size() > 0)
	{
		unsigned char charCode = mCharBuffer.front();
		mCharBuffer.pop();
		return charCode;
	}
	else
	{
		return 0;
	}
}

bool Keyboard::isCharEmpty() const
{
	return mCharBuffer.empty();
}

void Keyboard::flushKey()
{
	mKeyBuffer = std::queue<Event>();
}

void Keyboard::flushChar()
{
	mCharBuffer = std::queue<char>();
}

void Keyboard::flush()
{
	flushKey();
	flushChar();
}

void Keyboard::enableAutoRepeat()
{
	mAutoRepeat = true;
}

void Keyboard::disableAutoRepeat()
{
	mAutoRepeat = false;
}

bool Keyboard::autoRepeatEnabled() const
{
	return mAutoRepeat;
}

void Keyboard::onKeyPressed(uint32_t keyCode)
{
	mKeyStates[keyCode] = true;
	mKeyBuffer.push(Keyboard::Event(Keyboard::Event::EventType::Press, keyCode));
	trimBuffer(mKeyBuffer);
}

void Keyboard::onKeyReleased(uint32_t keyCode)
{
	mKeyStates[keyCode] = false;
	mKeyBuffer.push(Keyboard::Event(Keyboard::Event::EventType::Press, keyCode));
	trimBuffer(mKeyBuffer);
}

void Keyboard::onChar(char character)
{
	mCharBuffer.push(character);
	trimBuffer(mCharBuffer);
}

void Keyboard::clearState()
{
	mKeyStates.reset();
}

template<typename T>
void Keyboard::trimBuffer(std::queue<T>& buffer)
{
	while (buffer.size() > mBufferSize)
		buffer.pop();
}
