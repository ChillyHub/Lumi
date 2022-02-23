#pragma once

#include "pch.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Lumi
{
	class Shader
	{
	public:
		virtual ~Shader() = default;

		// active shader
		virtual Shader& Use() = 0;
		virtual void Use() const = 0;
		virtual void Unuse() const = 0;

		static std::shared_ptr<Shader> Create(const std::string& vertexSource, 
			const std::string& fragmentSource,
			const std::string& geometrySource = std::string());
	};
}
