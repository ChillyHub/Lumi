#pragma once

#include "Lumi/Core/Timestep.h"
#include "Lumi/Events/Event.h"
#include "Lumi/Events/ApplicationEvent.h"
#include "Lumi/ImGui/ImGuiLayer.h"
#include "Lumi/Renderer/Buffer.h"
#include "Lumi/Renderer/Renderer.h"
#include "Lumi/Renderer/Shader.h"
#include "Lumi/Renderer/VertexArray.h"
#include "Lumi/Scene/Camera.h"
#include "Lumi/Scene/Camera2D.h"
#include "Core.h"
#include "Input.h"
#include "LayerStack.h"
#include "Log.h"
#include "Window.h"

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
	protected:
		std::unique_ptr<Window> m_Window;
	private:
		ImGuiLayer* m_ImGuiLayer;
		LayerStack m_LayerStack;
		bool m_Running = true;

		float m_LastTime = 0.0f;

		static Application* s_Instance;

		// callback event
		bool OnCloseWindow(WindowCloseEvent& e);
		bool OnResizeWindow(WindowResizeEvent& e);
	};

	Application* CreateApplication();
}
