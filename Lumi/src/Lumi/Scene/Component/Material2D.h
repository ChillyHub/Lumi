#pragma once

#include "Component.h"

#include "pch.h"
#include "Lumi/Renderer/Texture.h"

#include <glm/glm.hpp>

namespace Lumi
{
	class Material2D : public Component
	{
	public:
		std::shared_ptr<Texture> Texture2D;
		glm::vec4 QuadColor = glm::vec4(1.0f);

	public:
		Material2D() = default;
		Material2D(const Material2D&) = default;
		Material2D(glm::vec4 color) : QuadColor(color) {}
		Material2D(glm::vec3 color) : QuadColor(glm::vec4(color, 1.0f)) {}
		Material2D(std::shared_ptr<Texture> texture2D, glm::vec4 color)
			: Texture2D(texture2D), QuadColor(color) {}
		Material2D(std::shared_ptr<Texture> texture2D, glm::vec3 color)
			: Texture2D(texture2D), QuadColor(glm::vec4(color, 1.0f)) {}
	};
}