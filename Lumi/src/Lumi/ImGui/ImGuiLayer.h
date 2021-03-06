#pragma once

#include "Lumi/Core/Layer.h"

namespace Lumi
{
	class LUMI_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event& event) override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;

		void SetDarkThemeColors();
	};
}
