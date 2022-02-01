#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace Lumi
{
	class LUMI_EXPORT Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	Application* CreateApplication();
}
