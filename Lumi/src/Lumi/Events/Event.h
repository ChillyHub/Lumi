#pragma once

#include "Lumi/Core.h"

#include <string>
#include <functional>

namespace Lumi
{
	enum class EventType 
	{
		NONE = 0,
		WINDOW_CLOSE, WINDOW_RESIZE, WINDOW_FOCUS, WINDOW_LOST_FOCUS, WINDOW_MOVED,
		APP_TICK, APP_UPDATE, APP_RENDER,
		KEY_PRESSED, KEY_RELEASED,
		MOUSE_BUTTON_PRESSED, MOUSE_BUTTON_RELEASED, MOUSE_MOVED, MOUSE_SCROLLED
	};

	enum EventCategory
	{
		NONE = 0,
		EVENT_CATEGORY_APPLICATION  = BIT(0),
		EVENT_CATEGORY_INPUT        = BIT(1),
		EVENT_CATEGORY_KEYBOARD     = BIT(2),
		EVENT_CATEGORY_MOUSE        = BIT(3),
		EVENT_CATEGORY_MOUSE_BUTTON = BIT(4)
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; } \
                               virtual EventType GetEventType() const override { return GetStaticType(); } \
                               virtual const char* GetName() const override { return #type; }

	class LUMI_EXPORT Event
	{
		friend class EventDispatcher;
	public:
		virtual EventType EventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}
	protected:
		bool m_Handled = false;
	};

	class EventDispatcher
	{
	public:
		EventDispatcher();
		~EventDispatcher();

	private:

	};

	EventDispatcher::EventDispatcher()
	{
	}

	EventDispatcher::~EventDispatcher()
	{
	}
}