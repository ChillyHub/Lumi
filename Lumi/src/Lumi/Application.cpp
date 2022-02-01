#include "pch.h"
#include "Application.h"

#include <GLFW/glfw3.h>

namespace Lumi
{
	
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallBack(BIND_EVENT_FN(OnEvent));
	}

	Application::~Application()
	{

	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispathcher(e);
		dispathcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(CloseWindow));

		LUMI_CORE_INFO("{0}",e);
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
			glClearColor(0.9f, 0.0f, 0.6f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}

	bool Application::CloseWindow(WindowCloseEvent& e)
	{
		return m_Running = false;
	}
}