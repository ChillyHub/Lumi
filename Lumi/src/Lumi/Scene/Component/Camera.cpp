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

	glm::mat4 Camera::GetWorldToClipMatrix() const
	{
		return m_ProjectionMatrix * m_ViewMatrix;
	}

	glm::vec3 Camera::WorldToScreenPoint(const glm::vec3& point) const
	{
		auto p = m_ProjectionMatrix * m_ViewMatrix * glm::vec4(point, 1.0f);
		float sx = p.x * ScreenWidth * 0.5f / p.w + ScreenWidth * 0.5f;
		float sy = p.y * ScreenHeight * 0.5f / p.w + ScreenHeight * 0.5f;
		return glm::vec3(sx, sy, p.z / p.w);
	}

	glm::vec3 Camera::ScreenToWorldVector(const glm::vec2& point) const
	{
		auto mat = glm::transpose(m_ViewMatrix);
		return mat * glm::vec4(point, 0.0f, 0.0f);
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
		glm::vec3 up = glm::rotate(transform.Rotation, { 0.0f, 1.0f, 0.0f });
		m_ViewMatrix = glm::lookAt(transform.Position, center, up);
	}

	void Camera::UpdateProjection()
	{
		if (Projection == ProjectionType::Perspective)
		{
			m_ProjectionMatrix = glm::perspective(glm::radians(Zoom), Aspect, NearClip, FarClip);
		}
		else
		{
			m_ProjectionMatrix = glm::ortho(-Aspect * Size * 0.5f, Aspect * Size * 0.5f,
				-Size * 0.5f, Size * 0.5f, NearClip, FarClip);
		}
	}
}