#pragma once

#include "Component.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Lumi
{
	class Transform : public Component
	{
	public:
		glm::vec3 Position = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Scale    = { 1.0f, 1.0f, 1.0f };
		glm::quat Rotation = { 1.0f, 0.0f, 0.0f, 0.0f };

	public:
		Transform() = default;
		Transform(const Transform&) = default;
		Transform(glm::vec3 position, glm::vec3 scale, glm::quat rotation)
			: Position(position), Scale(scale), Rotation(rotation) {}
	public:
		glm::mat4 GetModelMatrix();
		void LookAt();
		void RotateAroundPoint();
	public:
		virtual void OnUpdate(Timestep ts) override;
	private:
		glm::mat4 m_ModelMatrix = glm::mat4(1.0f);
	};
}