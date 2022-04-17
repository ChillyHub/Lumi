#pragma once

#include "pch.h"

#include "Component.h"

#include "Lumi/Renderer/Texture.h"

#include <glm/glm.hpp>

namespace Lumi
{
	class Entity;
	
	class Material2D : public Component
	{
	public:
		std::shared_ptr<Texture> Texture2D;
		glm::vec4 QuadColor = glm::vec4(1.0f);

		Entity* entity;
	public:
		Material2D(const Material2D&) = default;
		Material2D(Entity* ent) : entity(ent) {}
		Material2D(Entity* ent, glm::vec4 color)
			: entity(ent), QuadColor(color) {}
		Material2D(Entity* ent, glm::vec3 color)
			: entity(ent), QuadColor(glm::vec4(color, 1.0f)) {}
		Material2D(Entity* ent, std::shared_ptr<Texture> texture2D, glm::vec4 color)
			: entity(ent), Texture2D(texture2D), QuadColor(color) {}
		Material2D(Entity* ent, std::shared_ptr<Texture> texture2D, glm::vec3 color)
			: entity(ent), Texture2D(texture2D), QuadColor(glm::vec4(color, 1.0f)) {}
	};
}