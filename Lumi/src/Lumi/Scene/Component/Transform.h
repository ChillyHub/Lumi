#pragma once

#include "Component.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Lumi
{
	class Entity;
	
	class Transform : public Component
	{
	public:
		glm::vec3 Position = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Scale    = { 1.0f, 1.0f, 1.0f };
		glm::quat Rotation = { 1.0f, 0.0f, 0.0f, 0.0f };

		Entity* entity;
	public:
		Transform(const Transform& src) = default;
		Transform(Entity* ent) : entity(ent) {}
		Transform(Entity* ent, glm::vec3 position, glm::vec3 scale, glm::quat rotation)
			: entity(ent), Position(position), Scale(scale), Rotation(rotation) {}
	public:
		glm::mat4 GetModelMatrix() const;
		void LookAt(const glm::vec3& worldPos, const glm::vec3& worldUp = { 0.0f, 0.0f, 1.0f });
		void RotateAroundPoint(const glm::vec3& worldPos, const glm::vec3& axis, float angle);
	public:
		virtual void OnUpdate(Timestep ts) override;

		Transform& operator=(const Transform& rhs)
		{
			Position = rhs.Position;
			Scale = rhs.Scale;
			Rotation = rhs.Rotation;
			entity = rhs.entity;
			return *this;
		}
	private:
		glm::mat4 m_ModelMatrix = glm::mat4(1.0f);
	};
}