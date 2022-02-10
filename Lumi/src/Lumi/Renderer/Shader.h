#pragma once

#include "pch.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Lumi
{
	class Shader
	{
	public:
		// constructor and destructor
		Shader();
		Shader(const std::string& vertexSource, const std::string& fragmentSource, 
			const std::string& geometrySource = std::string());
		~Shader();

		unsigned int GetShaderID() const { return m_ShaderID; }

		// active shader
		Shader& Use();
		void Use() const;
		void Unuse() const;
		// compliles
		void Compile(const char* vertexSource, const char* fragmentSource, const char* geometrySource = nullptr);
		// utility functions
		void SetInt(const char* name, int value, bool useShader = false);
		void SetFloat(const char* name, float value, bool useShader = false);
		void SetVec2(const char* name, float x, float y, bool useShader = false);
		void SetVec2(const char* name, glm::vec2& value, bool useShader = false);
		void SetVec3(const char* name, float x, float y, float z, bool useShader = false);
		void SetVec3(const char* name, glm::vec3& value, bool useShader = false);
		void SetVec4(const char* name, float x, float y, float z, float w, bool useShader = false);
		void SetVec4(const char* name, glm::vec4& value, bool useShader = false);
		void SetMat4(const char* name, glm::mat4& value, bool useShader = false);
	private:
		// state
		unsigned int m_ShaderID;

		void CheckComplieErrors(unsigned int object, std::string type);
	};
}
