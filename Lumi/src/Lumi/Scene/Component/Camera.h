#pragma once

#include "Component.h"
#include "Lumi/Scene/Component/Transform.h"
#include "Lumi/Scene/Entity.h"

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

		Entity* entity;

		// camera options
		float MovementSpeed = 2.5f;
		// projection base
		float Zoom = 45.0f;
		float NearClip = 0.3f;
		float FarClip = 1000.0f;
		float Size = 2.0f;
		float Aspect = 16.0f / 9.0f;
		float ScreenWidth = 1980.0f;
		float ScreenHeight = 1080.0f;
	public:
		//Camera(const Camera& src) = default;
		Camera(Entity* ent) : entity(ent) {}
		Camera(Entity* ent, float moveSpeed, float zoom, float nearClip, float farClip,
			float size, float aspect)
			: entity(ent), MovementSpeed(moveSpeed), Zoom(zoom),
			NearClip(nearClip), FarClip(farClip), Size(size), Aspect(aspect) {}
	public:
		glm::mat4 GetViewMatrix() const;
		glm::mat4 GetProjectionMatrix() const;
		glm::mat4 GetWorldToScreenMatrix() const;
		glm::vec3 WorldToScreenPoint(const glm::vec3& point) const;
	public:
		virtual void OnUpdate(Timestep ts) override;
	private:
		void UpdateView();
		void UpdateProjection();
	private:
		glm::mat4 m_ViewMatrix = glm::mat4(1.0f);
		glm::mat4 m_ProjectionMatrix = glm::mat4(1.0f);
	};
}