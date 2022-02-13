#pragma once

#include "RendererAPI.h"

namespace Lumi
{
	class RenderCommand
	{
	public:
		static void SetColor(const glm::vec3& color)
		{
			s_RendererAPI->SetColor(color);
		}
		static void SetColor(const glm::vec4& color)
		{
			s_RendererAPI->SetColor(color);
		}
		static void SetColor(float r, float g, float b)
		{
			s_RendererAPI->SetColor(r, g, b);
		}
		static void SetColor(float r, float g, float b, float a)
		{
			s_RendererAPI->SetColor(r, g, b, a);
		}

		static void SetViewport(int width, int height)
		{
			s_RendererAPI->SetViewport(width, height);
		}

		static void Clear()
		{
			s_RendererAPI->Clear();
		}

		static void DrawArray(const std::shared_ptr<VertexArray>& vertexArray)
		{
			s_RendererAPI->DrawArray(vertexArray);
		}
		static void DrawIndex(const std::shared_ptr<VertexArray>& vertexArray)
		{
			s_RendererAPI->DrawIndex(vertexArray);
		}
	private:
		static RendererAPI* s_RendererAPI;
	};
}
