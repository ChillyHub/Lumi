#pragma once

#include "Lumi/Events/Event.h"
#include "Lumi/Events/ApplicationEvent.h"
#include "Lumi/ImGui/ImGuiLayer.h"
#include "Lumi/Renderer/Buffer.h"
#include "Lumi/Renderer/Renderer.h"
#include "Lumi/Renderer/Shader.h"
#include "Lumi/Renderer/VertexArray.h"
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
	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		LayerStack m_LayerStack;
		bool m_Running = true;

		std::shared_ptr<Shader> m_TriangleShader;
		std::shared_ptr<VertexArray> m_TriangleArray;

		std::shared_ptr<Shader> m_QuadShader;
		std::shared_ptr<VertexArray> m_QuadArray;

		static Application* s_Instance;

		bool CloseWindow(WindowCloseEvent& e);
	};

	Application* CreateApplication();
}
