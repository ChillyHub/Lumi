#pragma once

#include "Lumi/Core.h"
#include "Lumi/Events/Event.h"

namespace Lumi
{
	class LUMI_EXPORT Layer
	{
	public:
		Layer(const std::string& name = "Layer") : m_DebugName(name) { }
		virtual ~Layer() = default;

		const std::string& GetName() const { return m_DebugName; }

		virtual void OnAttach() { }
		virtual void OnDetach() { }
		virtual void OnUpdate() { }
		virtual void OnEvent(Event& event) { }
	protected:
		std::string m_DebugName;
	};
}
