#include "pch.h"
#include "Application.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Lumi
{
	Application* Application::s_Instance = nullptr;
	
	Application::Application()
	{
		LUMI_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;
		
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallBack(BIND_EVENT_FN(Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushLayer(m_ImGuiLayer);
	}

	Application::~Application()
	{

	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispathcher(e);
		dispathcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnCloseWindow));
		dispathcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(Application::OnResizeWindow));

		// LUMI_CORE_INFO("{0}", e);

		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
		{
			(*it)->OnEvent(e);
			if (e.m_Handled)
				break;
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach(); 
	}
	
	void Application::Run()
	{
		WindowResizeEvent e(1920, 1080);
		if (e.IsInCategory(EVENT_CATEGORY_APPLICATION))
		{
			LUMI_CLIENT_TRACE(e);
		}
		if (e.IsInCategory(EVENT_CATEGORY_INPUT))
		{
			LUMI_CLIENT_ERROR(e);
		}

		while (m_Running)
		{
			float time = (float)glfwGetTime();
			Timestep timestep = time - m_LastTime;
			m_LastTime = time;
			
			for (auto layer : m_LayerStack)
				layer->OnUpdate(timestep);

			m_ImGuiLayer->Begin();
			for (auto layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}


	bool Application::OnCloseWindow(WindowCloseEvent& e)
	{
		return m_Running = false;
	}

	bool Application::OnResizeWindow(WindowResizeEvent& e)
	{
		RenderCommand::SetViewport(m_Window->GetWidth(), m_Window->GetHeight());
		return false;
	}
}