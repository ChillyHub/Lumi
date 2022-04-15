#pragma once

#include <Lumi.h>

namespace Lumi
{
	class EditorLayer : public Layer
	{
	public:
		//EditorLayer();
		EditorLayer(unsigned int width, unsigned int height);
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
		std::shared_ptr<Scene> m_Scene;

		glm::vec3 m_QuadColor = { 0.113f, 0.113f, 0.113f };
		glm::vec3 m_LastColor = { 0.113f, 0.113f, 0.113f };
		glm::vec2 m_ViewportSize;
		bool m_ViewportFocus;
		bool m_ViewportHover;

		unsigned int m_ColorTex;
	};
}