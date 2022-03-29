#include <Lumi.h>
// Entry Point
#include "Lumi/Core/EntryPoint.h"

#include "EditorLayer.h"

#include "example/Example.hpp"

namespace Lumi
{
	class LumiEngine : public Application
	{
	public:
		LumiEngine()
		{
			PushLayer(new ExampleLayer(m_Window->GetWidth(), m_Window->GetHeight()));
			PushLayer(new EditorLayer());
		}

		~LumiEngine()
		{

		}
	};

	Application* CreateApplication()
	{
		return new LumiEngine();
	}
}