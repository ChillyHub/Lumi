#pragma once

#include "Event.h"

#include <sstream>

namespace Lumi
{
	class LUMI_EXPORT MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y)
			: m_MouseX(x), m_MouseY(y) { }

		float GetX() const { return m_MouseX; }
		float GetY() const { return m_MouseY; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvnet: ( " << m_MouseX << " , " << m_MouseY << " )";
			return ss.str();
		}

		EVENT_CLASS_TYPE(MOUSE_MOVED)
		EVENT_CLASS_CATEGORY(EVENT_CATEGORY_INPUT | EVENT_CATEGORY_MOUSE)
	private:
		float m_MouseX, m_MouseY;
	};

	class LUMI_EXPORT MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float offsetx, float offsety) 
			: m_OffsetX(offsetx), m_OffsetY(offsety) { }

		float GetOffsetX() const { return m_OffsetX; }
		float GetOffsetY() const { return m_OffsetY; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvenet: ( " << m_OffsetX << " , " << m_OffsetY << " )";
		}

		EVENT_CLASS_TYPE(MOUSE_SCROLLED)
		EVENT_CLASS_CATEGORY(EVENT_CATEGORY_INPUT | EVENT_CATEGORY_MOUSE)
	private:
		float m_OffsetX, m_OffsetY;
	};

	class LUMI_EXPORT MouseButtonEvent : public Event
	{
	public:
		int GetMouseButton() const { return m_Button; }

		EVENT_CLASS_CATEGORY(EVENT_CATEGORY_INPUT | EVENT_CATEGORY_MOUSE)
	protected:
		MouseButtonEvent(int button) : m_Button(button) { }

		int m_Button;
	};

	class LUMI_EXPORT MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button, int repeatCount) 
			: MouseButtonEvent(button), m_RepeatCount(repeatCount) { }

		int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvnet: " << m_Button << " (" << m_RepeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(MOUSE_BUTTON_PRESSED)
	private:
		int m_RepeatCount;
	};

	class LUMI_EXPORT MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) { }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasecEvnet: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MOUSE_BUTTON_RELEASED)
	};
}