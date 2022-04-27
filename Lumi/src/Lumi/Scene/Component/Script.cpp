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