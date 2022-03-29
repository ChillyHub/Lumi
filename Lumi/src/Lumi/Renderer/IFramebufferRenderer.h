#pragma once

#include "pch.h"

#include "Texture.h"
#include "VertexArray.h"
#include "Buffer.h"
#include "Shader.h"

#include <glm/glm.hpp>

namespace Lumi
{
	class IFramebufferRenderer
	{
	public:
		virtual void BeginFrameRender() = 0;
		virtual void EndFrameRender() = 0;

		virtual void DrawFrame(unsigned int index) = 0;
	protected:
		struct QuadVertex
		{
			glm::vec3 Position;
			glm::vec2 TexCoord;
			glm::vec4 Color;
			float TexIndex;
		};

		struct Renderer2DData
		{
			unsigned int IndexCount = 0;
			QuadVertex* VertexBufferBase = nullptr;
			QuadVertex* VertexBufferPtr = nullptr;

			std::shared_ptr<VertexArray> VAO;
			std::shared_ptr<VertexBuffer> VBO;
			std::shared_ptr<Shader> Shader;

			unsigned int CurrentIndex = 0;

			glm::vec4 QuadVertexPositions[4] = {
				{ -1.0f, -1.0f, 0.0f, 1.0f }, 
				{  1.0f, -1.0f, 0.0f, 1.0f },
				{  1.0f,  1.0f, 0.0f, 1.0f },
				{ -1.0f,  1.0f, 0.0f, 1.0f }
			};
		};
	};
}