#pragma once

#include <Lumi.h>

#include "EditorScene/EditorScene.h"
#include "EditorScene/EditorCamera2D.h"
#include "UI/PropertiesUI.h"
#include "UI/SceneUI.h"

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
		void NewScene();
		void OpenScene();
		void OpenScene(const std::filesystem::path& path);
		void SaveScene();
		void SaveSceneAs();
	private:
		bool OnKeyPressed(KeyPressedEvent& e);
		bool OnMousePressed(MouseButtonPressedEvent& e);
	private:

		std::shared_ptr<Framebuffer> m_Framebuffer;
		std::shared_ptr<Scene> m_Scene;
		std::shared_ptr<EditorScene> m_EditorScene;

		glm::vec3 m_QuadColor = { 0.113f, 0.113f, 0.113f };
		glm::vec3 m_LastColor = { 0.113f, 0.113f, 0.113f };
		glm::vec2 m_ViewportSize;
		bool m_ViewportFocus;
		bool m_ViewportHover;
		bool m_Move = false;
		bool m_Rote = false;
		bool m_Scal = false;

		unsigned int m_ColorTex;
		unsigned int m_CameraType = 1;
		int m_GizmosType = 0;
		int m_GizmosSpace = 1;
		std::string m_CurrentFilepath;

		std::shared_ptr<SceneUI> m_SceneUI 
			= std::shared_ptr<SceneUI>(new SceneUI());
		std::shared_ptr<PropertiesUI> m_PropertiesUI
			= std::shared_ptr<PropertiesUI>(new PropertiesUI());;
	};
}