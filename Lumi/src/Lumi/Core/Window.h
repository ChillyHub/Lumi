#pragma once

#include "pch.h"

#include "Lumi/Core/Core.h"
#include "Lumi/Events/Event.h"

namespace Lumi
{
	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "Lumi",
			unsigned int width = 1280, unsigned int height = 720) 
			: Title(title), Width(width), Height(height) { }
	};

	// Interface representing a desktop system based Window
	class LUMI_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() = default;

		virtual int GetWidth() const = 0;
		virtual int GetHeight() const = 0;
		virtual void SetWidth(int width) = 0;
		virtual void SetHeight(int height) = 0;
		virtual void UpdateWindowSize() = 0;

		virtual void* GetNativeWindow() const = 0;

		virtual void OnUpdate() = 0;

		// Window attributes
		virtual void SetEventCallBack(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());
	};
}