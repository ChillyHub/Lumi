#pragma once

#include "Component.h"
#include "Lumi/Scene/Component/Transform.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Lumi
{
	class Camera : public Component
	{
	public:
		bool Activated = true;
		ProjectionType Projection = ProjectionType::Perspective;

		// camera options
		float MovementSpeed = 2.5f;
		// projection base
		float Zoom = 45.0f;
		float NearClip = 0.1f;
		float FarClip = 1000.0f;
		int Width = 1920;
		int Height = 1080;
	public:
		Camera() = default;
		Camera(const Camera& src) = default;
		Camera(float moveSpeed, float zoom, float nearClip, float farClip, int width, int height)
			: MovementSpeed(moveSpeed), Zoom(zoom), 
			NearClip(nearClip), FarClip(farClip), Width(width), Height(height) {}
	public:
		glm::mat4& GetViewMatrix();
		glm::mat4& GetProjectionMatrix();
		glm::mat4& GetWorldToScreenMatrix();
		glm::vec3& WorldToScreenPoint(const glm::vec3& point);
	private:
		glm::mat4 m_ViewMatrix = glm::mat4(1.0f);
		glm::mat4 m_ProjectionMatrix = glm::mat4(1.0f);
	};
}