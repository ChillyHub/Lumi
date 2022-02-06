#pragma once

#include "Event.h"

namespace Lumi
{
	class LUMI_API KeyEvent : public Event
	{
	public:
		int GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EVENT_CATEGORY_INPUT | EVENT_CATEGORY_KEYBOARD)
	protected:
		KeyEvent(int keycode) : m_KeyCode(keycode) { }

		int m_KeyCode;
	};

	class LUMI_API KeyPressedEvent : public KeyEvent
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
	private:
		int m_RepeatCount;
	};

	class LUMI_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode) : KeyEvent(keycode) { }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KEY_RELEASED)
	};
}