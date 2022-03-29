#pragma once

#include <Lumi.h>

namespace Lumi
{
	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		~EditorLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate(Timestep ts) override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event& event) override;
	private:
		Camera2D m_Camera2D;
		Camera3D m_Camera3D;

		std::shared_ptr<Framebuffer> m_Framebuffer;
		std::shared_ptr<Texture> m_Texture;
	};
}