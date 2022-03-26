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

		// utility functions
		virtual void SetInt(const char* name, int value, bool useShader = false) = 0;
		virtual void SetIntV(const char* name, int* value, unsigned int count, bool useShader = false) = 0;
		virtual void SetFloat(const char* name, float value, bool useShader = false) = 0;
		virtual void SetFloatV(const char* name, float* value, unsigned int count, bool useShader = false) = 0;
		virtual void SetVec2(const char* name, float x, float y, bool useShader = false) = 0;
		virtual void SetVec2(const char* name, glm::vec2& value, bool useShader = false) = 0;
		virtual void SetVec2V(const char* name, float* value, unsigned int count, bool useShader = false) = 0;
		virtual void SetVec3(const char* name, float x, float y, float z, bool useShader = false) = 0;
		virtual void SetVec3(const char* name, glm::vec3& value, bool useShader = false) = 0;
		virtual void SetVec3V(const char* name, float* value, unsigned int count, bool useShader = false) = 0;
		virtual void SetVec4(const char* name, float x, float y, float z, float w, bool useShader = false) = 0;
		virtual void SetVec4(const char* name, glm::vec4& value, bool useShader = false) = 0;
		virtual void SetVec4V(const char* name, float* value, unsigned int count, bool useShader = false) = 0;
		virtual void SetMat4(const char* name, glm::mat4& value, bool useShader = false) = 0;

		static std::shared_ptr<Shader> Create(const std::string& vertexSource, 
			const std::string& fragmentSource,
			const std::string& geometrySource = std::string());
	};
}
