#include "pch.h"
#include "OpenGLContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Lumi
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		LUMI_CORE_ASSERT(m_WindowHandle, "Window handle is NULL!");
	}
	
	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);

		// init glad
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		LUMI_CORE_ASSERT(status, "Could not intialize glad!");

		LUMI_CORE_INFO("OpenGL info: ");
		LUMI_CORE_INFO("[            ");
		LUMI_CORE_INFO("  Vender:   {0}", glGetString(GL_VENDOR));
		LUMI_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		LUMI_CORE_INFO("  Version:  {0}", glGetString(GL_VERSION));
		LUMI_CORE_INFO("]            ");
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}