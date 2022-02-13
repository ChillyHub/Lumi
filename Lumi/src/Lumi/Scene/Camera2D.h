#pragma once

#include "Camera.h"

#include "Lumi/Window.h"
#include "Lumi/Core/Timestep.h"

#include "Lumi/Events/Event.h"
#include "Lumi/Events/ApplicationEvent.h"
#include "Lumi/Events/MouseEvent.h"

#include "Lumi/KeyCodes.h"
#include "Lumi/MouseButtonCodes.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Lumi
{
	class Camera2D : public Camera
	{
	public:
		enum class ProjectionType
		{
			Perspective = 0, Orthographic = 1
		};
	public:
		Camera2D() = default;
		Camera2D(int width, int height, glm::vec3 position = { 0.0f, 0.0f, 0.0f });

		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::vec3& GetPosition() const { return m_Position; }
		float GetRotation() const { return m_Rotation; }

		void SetPosition(float x, float y, float z)
		{
			m_Position = glm::vec3(x, y, z);
			UpdateView();
		}
		void SetPosition(const glm::vec3& position)
		{
			m_Position = position;
			UpdateView();
		}
		void SetRotation(float rotation)
		{
			m_Rotation = rotation;
			UpdateView();
		}

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);
	private:
		void UpdateView();
		void UpdateProjection();

		virtual bool OnMouseButtonPressed(MouseButtonPressedEvent& e);
		virtual bool OnMouseButtonRealeased(MouseButtonReleasedEvent& e);
		virtual bool OnScrolleMouse(MouseScrolledEvent& e);
		virtual bool OnMoveCursorPos(MouseMovedEvent& e);
		virtual bool OnResizeWindow(WindowResizeEvent& e);
	private:
		// projection type
		ProjectionType m_ProjectionType = ProjectionType::Orthographic;
		// cmaera attributes
		glm::vec3 m_Position            = { 0.0f, 0.0f, 0.0f };
								        
		// matrix				        
		glm::mat4 m_ViewMatrix          = glm::mat4(1.0f);
		// rotation				        
		float m_Rotation                = 0.0f;
								        
		// camera options		        
		float m_MovementSpeed           = 2.5f;
		float m_MouseMovedSensitivity   = 0.002f;
		float m_MouseScaleSensitivity   = 0.25f;
		// state
		float m_CursorPosX              = 0.0f;
		float m_CursorPosY              = 0.0f;
		bool m_MouseButtonLeftPressed   = false;
		bool m_MouseButtonMiddlePressed = false;
		bool m_MouseButtonRightPressed  = false;

		// projection base
		float m_Zoom                    = 45.0f;
		float m_NearClip                = 0.1f;
		float m_FarClip                 = 1000.0f;
		float m_OrthoScale              = 1.0f;
		float m_ScaleOffset             = 0.0f;
		int m_Width                     = 1920;
		int m_Height                    = 1080;
	};
}
