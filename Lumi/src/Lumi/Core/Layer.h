#pragma once

#include "Lumi/Core/Core.h"
#include "Lumi/Core/Timestep.h"
#include "Lumi/Events/Event.h"

namespace Lumi
{
	class LUMI_API Layer
	{
	public:
		Layer(const std::string& name = "Layer") : m_DebugName(name) { }
		virtual ~Layer() = default;

		const std::string& GetName() const { return m_DebugName; }

		virtual void OnAttach() { }
		virtual void OnDetach() { }
		virtual void OnUpdate(Timestep ts) { }
		virtual void OnImGuiRender() { }
		virtual void OnEvent(Event& event) { }
	protected:
		std::string m_DebugName;
	};
}
