#pragma once

#include "Lumi/Core/Log.h"
#include "Lumi/Core/Window.h"

#include "Lumi/Renderer/RenderContext.h"

#include <GLFW/glfw3.h>

namespace Lumi
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		virtual int GetWidth() const override { return m_Data.Width; }
		virtual int GetHeight() const override { return m_Data.Height; }
		virtual void SetWidth(int width) override { m_Data.Width = width; }
		virtual void SetHeight(int height) override { m_Data.Height = height; }

		virtual void* GetNativeWindow() const override { return m_Window; }

		virtual void UpdateWindowSize() override;

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
		RenderContext* m_Context;

		struct WindowData
		{
			std::string Title;
			int Width  = 1920;
			int Height = 1080;
			bool VSync = true;

			EventCallbackFn EventCallback;

		} m_Data;

		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
	};
}
