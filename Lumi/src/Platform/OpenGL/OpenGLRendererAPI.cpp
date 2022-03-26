#include "pch.h"
#include "OpenGLRendererAPI.h"

#include "Lumi/Core/Window.h"

#include <glad/glad.h>

namespace Lumi
{
	void OpenGLRendererAPI::Init()
	{
		LM_PROFILE_FUNCTION(); 
		
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_DEPTH_TEST);
	}
	
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

	void OpenGLRendererAPI::DrawIndex(const std::shared_ptr<VertexArray>& vertexArray, unsigned int count)
	{
		unsigned int indexCount = count ? count : vertexArray->GetIndexBuffer()->GetCount();
		glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, NULL);
	}
}