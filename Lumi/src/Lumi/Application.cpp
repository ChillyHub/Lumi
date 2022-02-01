#include "Application.h"

#include "Lumi/Log.h"
#include "Lumi/Events/ApplicationEvent.h"

namespace Lumi
{
	
	Application::Application()
	{

	}

	Application::~Application()
	{

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

		while (true);
	}
}