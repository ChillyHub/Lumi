#pragma once

#include "Lumi/Renderer/RendererAPI.h"

namespace Lumi
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void SetColor(const glm::vec3& color) override;
		virtual void SetColor(const glm::vec4& color) override;
		virtual void SetColor(float r, float g, float b) override;
		virtual void SetColor(float r, float g, float b, float a) override;

		virtual void Clear() override;

		virtual void DrawArray(const std::shared_ptr<VertexArray>& vertexArray) override;
		virtual void DrawIndex(const std::shared_ptr<VertexArray>& vertexArray) override;
	};
}
