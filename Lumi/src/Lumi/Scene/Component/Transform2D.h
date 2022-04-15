#pragma once

#include "Component.h"

#include <glm/glm.hpp>

namespace Lumi
{
	class Transform2D : public Component
	{
	public:
		glm::vec3 Position = { 0.0f, 0.0f, 0.0f };
		glm::vec2 Scale    = { 1.0f, 1.0f };
		float Rotation     = 0.0f;

	public:
		Transform2D() = default;
		Transform2D(const Transform2D&) = default;
		Transform2D(glm::vec2 position, glm::vec2 scale, float rotation)
			: Position(glm::vec3(position.x, position.y, 0.0f)), Scale(scale), Rotation(rotation) {}
		Transform2D(glm::vec3 position, glm::vec2 scale, float rotation)
			: Position(position), Scale(scale), Rotation(rotation) {}
	};
}