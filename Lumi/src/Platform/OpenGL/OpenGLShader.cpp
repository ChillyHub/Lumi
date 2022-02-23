#include "pch.h"
#include "OpenGLShader.h"

#include <glad/glad.h>

namespace Lumi
{
	OpenGLShader::OpenGLShader()
		: m_ShaderID(0)
	{

	}

	OpenGLShader::OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource,
		const std::string& geometrySource)
		: m_ShaderID(0)
	{
		Compile(vertexSource.c_str(), fragmentSource.c_str(),
			geometrySource.empty() ? nullptr : geometrySource.c_str());
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(this->m_ShaderID);
	}

	OpenGLShader& OpenGLShader::Use()
	{
		glUseProgram(this->m_ShaderID);
		return *this;
	}

	void OpenGLShader::Use() const
	{
		glUseProgram(this->m_ShaderID);
	}

	void OpenGLShader::Unuse() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::Compile(const char* vertexSource, const char* fragmentSource, const char* geometrySource)
	{
		if (m_ShaderID)
		{
			LUMI_CORE_INFO("Shader have allready been compiled!");
			return;
		}

		unsigned int sVertex, sFragment, sGeometry;
		// vertex shader
		sVertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(sVertex, 1, &vertexSource, NULL);
		glCompileShader(sVertex);
		CheckComplieErrors(sVertex, "VERTEX");
		// fragment shader
		sFragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(sFragment, 1, &fragmentSource, NULL);
		glCompileShader(sFragment);
		CheckComplieErrors(sFragment, "FRAGMENT");
		// geometry shader
		if (geometrySource != nullptr)
		{
			sGeometry = glCreateShader(GL_GEOMETRY_SHADER);
			glShaderSource(sGeometry, 1, &geometrySource, NULL);
			glCompileShader(sGeometry);
			CheckComplieErrors(sGeometry, "GEOMETRY");
		}

		// shader program
		this->m_ShaderID = glCreateProgram();
		glAttachShader(this->m_ShaderID, sVertex);
		glAttachShader(this->m_ShaderID, sFragment);
		if (geometrySource != nullptr)
			glAttachShader(this->m_ShaderID, sGeometry);
		glLinkProgram(this->m_ShaderID);
		CheckComplieErrors(this->m_ShaderID, "PROGRAM");

		// delete the linked shaders
		glDeleteShader(sVertex);
		glDeleteShader(sFragment);
		if (geometrySource != nullptr)
			glDeleteShader(sGeometry);

		// allways detach shaders after a successful link
		glDetachShader(this->m_ShaderID, sVertex);
		glDetachShader(this->m_ShaderID, sFragment);
		if (geometrySource != nullptr)
			glDetachShader(this->m_ShaderID, sGeometry);
	}

	void OpenGLShader::SetInt(const char* name, int value, bool useShader)
	{
		if (useShader)
			this->Use();
		glUniform1i(glGetUniformLocation(this->m_ShaderID, name), value);
	}
	void OpenGLShader::SetFloat(const char* name, float value, bool useShader)
	{
		if (useShader)
			this->Use();
		glUniform1f(glGetUniformLocation(this->m_ShaderID, name), value);
	}
	void OpenGLShader::SetVec2(const char* name, float x, float y, bool useShader)
	{
		if (useShader)
			this->Use();
		glUniform2f(glGetUniformLocation(this->m_ShaderID, name), x, y);
	}
	void OpenGLShader::SetVec2(const char* name, const glm::vec2& value, bool useShader)
	{
		if (useShader)
			this->Use();
		glUniform2f(glGetUniformLocation(this->m_ShaderID, name), value.x, value.y);
	}
	void OpenGLShader::SetVec3(const char* name, float x, float y, float z, bool useShader)
	{
		if (useShader)
			this->Use();
		glUniform3f(glGetUniformLocation(this->m_ShaderID, name), x, y, z);
	}
	void OpenGLShader::SetVec3(const char* name, const glm::vec3& value, bool useShader)
	{
		if (useShader)
			this->Use();
		glUniform3f(glGetUniformLocation(this->m_ShaderID, name), value.x, value.y, value.z);
	}
	void OpenGLShader::SetVec4(const char* name, float x, float y, float z, float w, bool useShader)
	{
		if (useShader)
			this->Use();
		glUniform4f(glGetUniformLocation(this->m_ShaderID, name), x, y, z, w);
	}
	void OpenGLShader::SetVec4(const char* name, const glm::vec4& value, bool useShader)
	{
		if (useShader)
			this->Use();
		glUniform4f(glGetUniformLocation(this->m_ShaderID, name), value.x, value.y, value.z, value.w);
	}
	void OpenGLShader::SetMat4(const char* name, const glm::mat4& value, bool useShader)
	{
		if (useShader)
			this->Use();
		glUniformMatrix4fv(glGetUniformLocation(this->m_ShaderID, name), 1, false, glm::value_ptr(value));
	}

	void OpenGLShader::CheckComplieErrors(unsigned int object, std::string type)
	{
		int success;
		char infoLog[1024];
		if (type != "PROGRAM")
		{
			glGetShaderiv(object, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(object, 1024, NULL, infoLog);
				LUMI_CORE_ERROR("| ERROR::SHADER: Compile-time error: Type: {0}", type);
				LUMI_CORE_ERROR("{0}", infoLog);
				LUMI_CORE_ERROR(" -- --------------------------------------------------- -- ");
				LUMI_CORE_ASSERT(false, "\n");
			}
		}
		else
		{
			glGetShaderiv(object, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(object, 1024, NULL, infoLog);
				LUMI_CORE_ERROR("| ERROR::SHADER: Link-time error: Type: {0}", type);
				LUMI_CORE_ERROR("{0}", infoLog);
				LUMI_CORE_ERROR(" -- --------------------------------------------------- -- ");
				LUMI_CORE_ASSERT(false, "\n");
			}
		}
	}
}