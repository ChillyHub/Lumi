#include "pch.h"

#include "Camera.h"

namespace Lumi
{
	glm::mat4 Camera::GetViewMatrix() const
	{
		return m_ViewMatrix;
	}

	glm::mat4 Camera::GetProjectionMatrix() const
	{
		return m_ProjectionMatrix;
	}

	glm::mat4 Camera::GetWorldToScreenMatrix() const
	{
		return m_ProjectionMatrix * m_ViewMatrix;
	}

	glm::vec3 Camera::WorldToScreenPoint(const glm::vec3& point) const
	{
		return m_ProjectionMatrix * m_ViewMatrix * glm::vec4(point, 1.0f);
	}

	void Camera::OnUpdate(Timestep ts)
	{
		UpdateView();
		UpdateProjection();
	}

	void Camera::UpdateView()
	{
		auto& transform = entity->transform;
		glm::vec3 center = glm::rotate(transform.Rotation, { 0.0f, 0.0f, -1.0f }) + transform.Position;
		m_ViewMatrix = glm::lookAt(transform.Position, center, { 0.0f, 1.0f, 0.0f });
	}

	void Camera::UpdateProjection()
	{
		if (Projection == ProjectionType::Perspective)
		{
			m_ProjectionMatrix = glm::perspective(Zoom, Aspect, NearClip, FarClip);
		}
		else
		{
			m_ProjectionMatrix = glm::ortho(-Aspect * Size * 0.5f, Aspect * Size * 0.5f,
				-Size * 0.5f, Size * 0.5f, NearClip, FarClip);
		}
	}
}