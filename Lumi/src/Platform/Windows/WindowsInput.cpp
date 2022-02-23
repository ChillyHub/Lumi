#include "pch.h"
#include "WindowsInput.h"

#include "Lumi/Core/Application.h"

#include <GLFW/glfw3.h>

namespace Lumi
{
	Input* Input::s_Instance = new WindowsInput();

	bool WindowsInput::IsKeyPressedImpl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::IsMouseButtonPressedImpl(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	std::pair<float, float> WindowsInput::GetCursorPosImpl()
	{
		double xpos, ypos;
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		glfwGetCursorPos(window, &xpos, &ypos);
		return { (float)xpos, (float)ypos };
	}

	float WindowsInput::GetCursorXImpl()
	{
		auto [xpos, ypos] = GetCursorPosImpl();
		return xpos;
	}

	float WindowsInput::GetCursorYImpl()
	{
		auto [xpos, ypos] = GetCursorPosImpl();
		return ypos;
	}
}