#include "pch.h"
#include "Application.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Lumi
{
	Application* Application::s_Instance = nullptr;
	
	Application::Application()
	{
		LM_PROFILE_FUNCTION();
		
		LUMI_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;
		
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallBack(BIND_EVENT_FN(Application::OnEvent));

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushLayer(m_ImGuiLayer);
	}

	Application::~Application()
	{
		LM_PROFILE_FUNCTION();
	}

	void Application::OnEvent(Event& e)
	{
		LM_PROFILE_FUNCTION();
		
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
		LM_PROFILE_FUNCTION();
		
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		LM_PROFILE_FUNCTION();
		
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach(); 
	}
	
	void Application::Run()
	{
		LM_PROFILE_FUNCTION();

		while (m_Running)
		{
			float time = (float)glfwGetTime();
			Timestep timestep = time - m_LastTime;
			if (m_Minimize && timestep < 0.1) continue;
			m_LastTime = time;
			
			if (!m_Minimize)
			{
				for (auto layer : m_LayerStack)
					layer->OnUpdate(timestep);
			}

			m_ImGuiLayer->Begin();
			for (auto layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	void Application::Close()
	{
		LM_PROFILE_FUNCTION();

		m_Running = false;
	}


	bool Application::OnCloseWindow(WindowCloseEvent& e)
	{
		return m_Running = false;
	}

	bool Application::OnResizeWindow(WindowResizeEvent& e)
	{
		unsigned int width = e.GetWidth();
		unsigned int height = e.GetHeight();
		if (width == 0 || height == 0)
		{
			m_Minimize = true;
		}
		else
		{
			m_Minimize = false;
		}
		
		RenderCommand::SetViewport(width, height);
		return false;
	}
}