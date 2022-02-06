#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Window.h"

#include "Lumi/Events/ApplicationEvent.h"
#include "Input.h"
#include "Lumi/LayerStack.h"
#include "Lumi/Log.h"

namespace Lumi
{
	class LUMI_API Application
	{
	public:
		Application();
		virtual ~Application();

		Window& GetWindow() { return *m_Window; }
		static Application& Get() { return *s_Instance; }

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		void Run();
	private:
		Window* m_Window;
		LayerStack m_LayerStack;
		bool m_Running = true;

		static Application* s_Instance;

		bool CloseWindow(WindowCloseEvent& e);
	};

	Application* CreateApplication();
}
