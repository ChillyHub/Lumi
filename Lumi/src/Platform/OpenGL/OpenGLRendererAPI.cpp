#include "pch.h"
#include "OpenGLRendererAPI.h"

#include "Lumi/Window.h"

#include <glad/glad.h>

namespace Lumi
{
	void OpenGLRendererAPI::SetColor(const glm::vec3& color)
	{
		glClearColor(color.r, color.g, color.b, 1.0f);
	}

	void OpenGLRendererAPI::SetColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::SetColor(float r, float g, float b)
	{
		glClearColor(r, g, b, 1.0f);
	}

	void OpenGLRendererAPI::SetColor(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
	}

	void OpenGLRendererAPI::SetViewport(int width, int height)
	{
		glViewport(0, 0, (unsigned int)width, (unsigned int)height);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	
	void OpenGLRendererAPI::DrawArray(const std::shared_ptr<VertexArray>& vertexArray)
	{
		glDrawArrays(GL_TRIANGLES, 0, vertexArray->GetVertexCount());
	}

	void OpenGLRendererAPI::DrawIndex(const std::shared_ptr<VertexArray>& vertexArray)
	{
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, NULL);
	}
}