#include "pch.h"
#include "Camera3D.h"

namespace Lumi
{
	Camera3D::Camera3D(int width, int height, glm::vec3 position, glm::vec3 focalPoint)
		: m_Width(width), m_Height(height), m_Position(position), m_FocalPoint(focalPoint)
	{
		UpdateView();
		UpdateProjection();
	}

	void Camera3D::OnUpdate()
	{

	}

	void Camera3D::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		//dispatcher.Dispatch<>;
	}
	
	void Camera3D::UpdateFront()
	{
		glm::vec3 front;
		front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		front.y = sin(glm::radians(m_Pitch));
		front.z = -sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		m_Front = glm::normalize(front);
		m_Quaternion = glm::quat(m_Front);
		m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
		m_Up = glm::normalize(glm::cross(m_Right, m_Front));
	}

	void Camera3D::UpdateView()
	{
		UpdateFront();
		m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
	}

	void Camera3D::UpdateProjection()
	{
		if (m_ProjectionType == ProjectionType::Perspective)
			m_ProjectMatrix = glm::perspective(m_Zoom, (float)m_Width / (float)m_Height, m_NearClip, m_FarClip);
		else
			m_ProjectMatrix = glm::ortho(-(float)m_Width / (float)m_Width,
				(float)m_Width / (float)m_Width, -1.0f, 1.0f, -1.0f, 1.0f);
	}
}