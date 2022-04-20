#pragma once

#include "Lumi/Core/Timestep.h"
#include "Lumi/Events/Event.h"
#include "Lumi/Events/ApplicationEvent.h"
#include "Lumi/Events/MouseEvent.h"
#include "Lumi/Events/KeyEvent.h"

namespace Lumi
{
	enum class ProjectionType
	{
		Perspective = 0, Orthographic = 1
	};
	
	class Component
	{
	public:
		virtual void OnEvent(Event& e) {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void Disposed() {}
	};
}