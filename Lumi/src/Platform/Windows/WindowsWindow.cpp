#include "pch.h"
#include "WindowsWindow.h"

#include "Lumi/Events/ApplicationEvent.h"
#include "Lumi/Events/KeyEvent.h"
#include "Lumi/Events/MouseEvent.h"

#include "Platform/OpenGL/OpenGLContext.h"

namespace Lumi
{
	static bool s_GLFWInitialized = false;

	static void glfwErrorCallback(int error, const char* descirption)
	{
		LUMI_CORE_ERROR("GLFW Error ({0}): {1}", error, descirption);
	}

	Window* Window::Create(const WindowProps& props)
	{
		LM_PROFILE_FUNCTION(); 
		
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		LM_PROFILE_FUNCTION(); 
		
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		LM_PROFILE_FUNCTION(); 
		
		Shutdown();
	}

	void WindowsWindow::OnUpdate()
	{
		LM_PROFILE_FUNCTION(); 
		
		LUMI_CORE_ASSERT(m_Window, "Window handle is NULL!");
		glfwPollEvents();
		m_Context->SwapBuffers();
		glfwSetWindowTitle(m_Window, m_Data.Title.c_str());
	}

	void WindowsWindow::UpdateWindowSize()
	{
		glfwGetWindowSize(m_Window, &m_Data.Width, &m_Data.Height);
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		LM_PROFILE_FUNCTION(); 
		
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		LUMI_CORE_INFO("Creating window {0} ( {1} , {2} )", props.Title, props.Width, props.Height);

		if (!s_GLFWInitialized)
		{
			// init GLFW
			int success = glfwInit();
			LUMI_CORE_ASSERT(success, "Could not intialize GLFW!");
			glfwWindowHint(GLFW_MAXIMIZED, GL_TRUE);
			glfwSetErrorCallback(glfwErrorCallback);
			s_GLFWInitialized = true;
		}

		// create window
		m_Window = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
		m_Context = new OpenGLContext(m_Window);
		m_Context->Init();
		glfwSetWindowUserPointer(m_Window, &m_Data);

		SetVSync(true);
		UpdateWindowSize();

		// set GLFW callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.Width = width;
				data.Height = height;

				WindowResizeEvent event(width, height);
				data.EventCallback(event);
			});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				WindowCloseEvent event;
				data.EventCallback(event);
			});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mode)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.EventCallback(event);
					break;
				}
				default:
					break;
				}
			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double posX, double posY)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseMovedEvent event((float)posX, (float)posY);
				data.EventCallback(event);
			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double offsetX, double offsetY)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseScrolledEvent event((float)offsetX, (float)offsetY);
				data.EventCallback(event);
			});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mode)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					MouseButtonPressedEvent event(button, 1);
					data.EventCallback(event);
					break;
				}
				default:
					break;
				}
			});
	}

	void WindowsWindow::Shutdown()
	{
		LM_PROFILE_FUNCTION(); 
		
		glfwDestroyWindow(m_Window);
	}
}