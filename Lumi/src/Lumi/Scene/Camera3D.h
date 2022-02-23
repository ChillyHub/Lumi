#pragma once

#include "Camera.h"

#include "Lumi/Core/KeyCodes.h"
#include "Lumi/Core/MouseButtonCodes.h"
#include "Lumi/Core/Timestep.h"
#include "Lumi/Core/Window.h"

#include "Lumi/Events/Event.h"
#include "Lumi/Events/ApplicationEvent.h"
#include "Lumi/Events/MouseEvent.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Lumi
{
	class Camera3D : public Camera
	{
	public:
		enum class ProjectionType
		{
			Perspective = 0, Orthographic = 1
		};
	public:
		Camera3D() = default;
		Camera3D(int width, int height, 
			glm::vec3 position = { 0.0f, 0.0f, 0.0f }, 
			glm::vec3 focalPoint = { 0.0f, 0.0f, -1.0f });

		const glm::vec3& GetPosition() const { return m_Position; }
		const glm::vec3& GetFocalPoint() const { return m_FocalPoint; }
		const glm::quat& GetQuaternion() const { return m_Quaternion; }
		float GetYaw() const { return m_Yaw; }
		float GetPitch() const { return m_Pitch; }

		void SetProjectionType(ProjectionType type)
		{
			if (m_ProjectionType != type)
			{
				m_ProjectionType = type;
				UpdateProjection();
			}
		}

		void UpdateViewportSize(int width, int height)
		{
			m_Width = width;
			m_Height = height;
			UpdateProjection();
		}

		void OnUpdate();
		void OnEvent(Event& e);
	private:
		void UpdateFront();
		void UpdateView();
		void UpdateProjection();
	private:
		// projection type
		ProjectionType m_ProjectionType = ProjectionType::Perspective;
		// cmaera attributes
		glm::vec3 m_Position      = {0.0f, 0.0f,  0.0f};
		glm::vec3 m_Front         = {0.0f, 0.0f, -1.0f};
		glm::vec3 m_Up            = {0.0f, 1.0f,  0.0f};
		glm::vec3 m_Right         = {1.0f, 0.0f,  0.0f};
		glm::vec3 m_WorldUp       = {0.0f, 1.0f,  0.0f};
		glm::vec3 m_FocalPoint    = {0.0f, 0.0f, -1.0f};

		// Rotation
		// matrix
		glm::mat4 m_ViewMatrix    = glm::mat4(1.0f);
		// quaternion
		glm::quat m_Quaternion    = glm::quat(0.0f, 0.0f, 0.0f, 1.0f);
		// eular angles
		float m_Yaw               = 0.0f;
		float m_Pitch             = 0.0f;

		// camera options
		float m_MovementSpeed     = 2.5f;
		float m_MouseSensitivity  = 0.05f;
		// projection base
		float m_Zoom              = 45.0f;
		float m_NearClip          = 0.1f;
		float m_FarClip           = 1000.0f;
		int m_Width               = 1920;
		int m_Height              = 1080;
	};
}
