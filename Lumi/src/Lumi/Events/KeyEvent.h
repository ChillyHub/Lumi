#pragma once

#include "Event.h"

#include <sstream>

namespace Lumi
{
	class LUMI_EXPORT KeyEvent : public Event
	{
	public:
		int GetKeyCode() const { return m_KeyCode; }

	protected:
		KeyEvent(int keycode) : m_KeyCode(keycode) { }

		int m_KeyCode;
	};

	class LUMI_EXPORT KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keycode, int repeatCount)
			: KeyEvent(keycode), m_RepeatCount(repeatCount) { }

		int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KEY_PRESSED)
	protected:
		int m_RepeatCount;
	};

	class LUMI_EXPORT KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode) : KeyEvent(keycode) { }
	protected:
		int m;
	};
}