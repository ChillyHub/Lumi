#pragma once

#include "Lumi/Core/Timestep.h"

namespace Lumi
{
	enum class ProjectionType
	{
		Perspective = 0, Orthographic = 1
	};
	
	class Component
	{
	public:
		virtual void OnUpdate(Timestep ts) {}
		virtual void Disposed() {}
	};
}