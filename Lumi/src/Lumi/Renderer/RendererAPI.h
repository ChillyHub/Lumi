#pragma once

#include "VertexArray.h"

#include <glm/glm.hpp>

namespace Lumi
{
	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0,
			OpenGL = 1,
			Vulkan = 2,
			DirectX = 3
		};

		static API GetAPI() { return m_API; }

		virtual void SetColor(const glm::vec3& color) = 0;
		virtual void SetColor(const glm::vec4& color) = 0;
		virtual void SetColor(float r, float g, float b) = 0;
		virtual void SetColor(float r, float g, float b, float a) = 0;

		virtual void SetViewport(int width, int height) = 0;

		virtual void Clear() = 0;

		virtual void DrawArray(const std::shared_ptr<VertexArray>& vertexArray) = 0;
		virtual void DrawIndex(const std::shared_ptr<VertexArray>& vertexArray) = 0;
	private:
		static API m_API;
	};
}
