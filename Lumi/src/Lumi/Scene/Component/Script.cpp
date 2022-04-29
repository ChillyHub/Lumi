#include "pch.h"

#include "Script.h"
#include "Lumi/Scene/Entity.h"

namespace Lumi
{
	void Script::Init()
	{
		if (InitScript == nullptr)
		{
			Bind<Script>();
		}
		instance = InitScript();
		instance->Start();
	}

	void Script::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseButtonPressedEvent>(
			BIND_EVENT_DYNAMIC_FN(Script::OnMouseButtonPressed, instance));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(
			BIND_EVENT_DYNAMIC_FN(Script::OnMouseButtonRealeased, instance));
		dispatcher.Dispatch<MouseScrolledEvent>(
			BIND_EVENT_DYNAMIC_FN(Script::OnScrolleMouse, instance));
		dispatcher.Dispatch<MouseMovedEvent>(
			BIND_EVENT_DYNAMIC_FN(Script::OnMoveCursorPos, instance));
		dispatcher.Dispatch<WindowResizeEvent>(
			BIND_EVENT_DYNAMIC_FN(Script::OnResizeWindow, instance));
	}

	void Script::OnUpdate(Timestep ts)
	{
		instance->Update(ts);
	}

	void Script::Disposed()
	{
		delete instance;
		instance = nullptr;
	}
}