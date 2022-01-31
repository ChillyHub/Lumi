#pragma once

#include "Event.h"

#include <sstream>

namespace Lumi
{
	class LUMI_EXPORT WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent();
		~WindowResizeEvent();

	private:

	};

	WindowResizeEvent::WindowResizeEvent()
	{
	}

	WindowResizeEvent::~WindowResizeEvent()
	{
	}
}