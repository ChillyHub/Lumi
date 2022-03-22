#pragma once

#include "pch.h"

#include "Lumi/Renderer/Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Lumi
{
	class OpenGLShader : public Shader
	{
	public:
		// constructor and destructor
		OpenGLShader();
		OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource,
			const std::string& geometrySource = std::string());
		~OpenGLShader();

		unsigned int GetShaderID() const { return m_ShaderID; }

		// active shader
		virtual OpenGLShader& Use() override;
		virtual void Use() const override;
		virtual void Unuse() const override;
		// compliles
		void Compile(const char* vertexSource, const char* fragmentSource, const char* geometrySource = nullptr);
		// utility functions
		virtual void SetInt(const char* name, int value, bool useShader = false) override;
		virtual void SetFloat(const char* name, float value, bool useShader = false) override;
		virtual void SetVec2(const char* name, float x, float y, bool useShader = false) override;
		virtual void SetVec2(const char* name, const glm::vec2& value, bool useShader = false) override;
		virtual void SetVec3(const char* name, float x, float y, float z, bool useShader = false) override;
		virtual void SetVec3(const char* name, const glm::vec3& value, bool useShader = false) override;
		virtual void SetVec4(const char* name, float x, float y, float z, float w, bool useShader = false) override;
		virtual void SetVec4(const char* name, const glm::vec4& value, bool useShader = false) override;
		virtual void SetMat4(const char* name, const glm::mat4& value, bool useShader = false) override;
	private:
		// state
		unsigned int m_ShaderID;

		void CheckComplieErrors(unsigned int object, std::string type);
	};
}

