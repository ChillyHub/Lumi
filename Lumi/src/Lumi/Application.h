#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Window.h"

#include "Lumi/Log.h"
#include "Lumi/Events/ApplicationEvent.h"

namespace Lumi
{
	class LUMI_EXPORT Application
	{
	public:
		Application();
		virtual ~Application();

		void OnEvent(Event& e);
		void Run();
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;

		bool CloseWindow(WindowCloseEvent& e);
	};

	Application* CreateApplication();
}
