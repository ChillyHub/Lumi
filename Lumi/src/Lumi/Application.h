#pragma once

#include "Core.h"

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
