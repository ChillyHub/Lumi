#include "pch.h"

#include "Lumi/Core/Application.h"
#include "Lumi/Core/Input.h"

#include <GLFW/glfw3.h>

namespace Lumi
{
	bool Input::IsKeyPressed(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Input::IsMouseButtonPressed(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	std::pair<float, float> Input::GetCursorPos()
	{
		double xpos, ypos;
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		glfwGetCursorPos(window, &xpos, &ypos);
		return { (float)xpos, (float)ypos };
	}

	float Input::GetCursorX()
	{
		auto [xpos, ypos] = GetCursorPos();
		return xpos;
	}

	float Input::GetCursorY()
	{
		auto [xpos, ypos] = GetCursorPos();
		return ypos;
	}
}