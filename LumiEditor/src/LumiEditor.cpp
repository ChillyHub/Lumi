#include <Lumi.h>
// Entry Point
#include "Lumi/Core/EntryPoint.h"

#include "EditorLayer.h"

namespace Lumi
{
	class LumiEditor : public Application
	{
	public:
		LumiEditor()
		{
			//PushLayer(new ExampleLayer(m_Window->GetWidth(), m_Window->GetHeight()));
			PushLayer(new EditorLayer(m_Window->GetWidth(), m_Window->GetHeight()));
		}

		~LumiEditor()
		{

		}
	};

	Application* CreateApplication()
	{
		return new LumiEditor();
	}
}