#pragma once

#include "Lumi/Window.h"
#include "Lumi/Log.h"

#include <GLFW/glfw3.h>

namespace Lumi
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		unsigned int GetWidth() const override { return m_Data.Width; }
		unsigned int GetHeight() const override { return m_Data.Height; }

		void OnUpdate() override;

		// Window attributes
		void SetEventCallBack(const EventCallbackFn& callback) override
		{
			m_Data.EventCallback = callback;
		}
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;
	private:
		GLFWwindow* m_Window;

		struct WindowData
		{
			std::string Title;
			unsigned int Width;
			unsigned int Height;
			bool VSync;

			EventCallbackFn EventCallback;

		} m_Data;

		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
	};
}
