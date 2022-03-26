#pragma once

#include "RenderCommand.h"
#include "Renderer.h"
#include "Shader.h"

#include "Lumi/Core/ResourceManager.h"

namespace Lumi
{
	class Renderer2D
	{
	public:
		static void Init();

		static void BeginScene(const Camera2D& camera);
		static void EndScene();
		static void Flush();

		static void DrawQuad(const glm::vec2& position = glm::vec2(0.0f),
			const glm::vec2& size = glm::vec2(1.0f),
			const glm::vec3& color = glm::vec3(1.0f), 
			float rotate = 0.0f);
		static void DrawQuad(const glm::vec2& position,
			const glm::vec2& size,
			const glm::vec4& color, 
			float rotate = 0.0f);
		static void DrawQuad(const glm::vec3& position,
			const glm::vec2& size = glm::vec2(1.0f),
			const glm::vec3& color = glm::vec3(1.0f), 
			float rotate = 0.0f);
		static void DrawQuad(const glm::vec3& position,
			const glm::vec2& size,
			const glm::vec4& color, 
			float rotate = 0.0f);
		static void DrawQuad(std::shared_ptr<Texture> texture, 
			const glm::vec2& position = glm::vec2(0.0f),
			const glm::vec2& size = glm::vec2(1.0f),
			const glm::vec3& color = glm::vec3(1.0f), 
			float rotate = 0.0f);
		static void DrawQuad(std::shared_ptr<Texture> texture, 
			const glm::vec2& position,
			const glm::vec2& size,
			const glm::vec4& color, 
			float rotate = 0.0f);
		static void DrawQuad(std::shared_ptr<Texture> texture, 
			const glm::vec3& position,
			const glm::vec2& size = glm::vec2(1.0f),
			const glm::vec3& color = glm::vec3(1.0f), 
			float rotate = 0.0f);
		static void DrawQuad(std::shared_ptr<Texture> texture, 
			const glm::vec3& position,
			const glm::vec2& size,
			const glm::vec4& color, 
			float rotate = 0.0f);
	private:
		struct QuadVertex
		{
			glm::vec3 Position;
			glm::vec2 TexCoord;
			glm::vec4 Color;
			float TexIndex;
		};

		struct Renderer2DData
		{
			static const unsigned int MaxQuads = 10000;
			static const unsigned int MaxVertices = MaxQuads * 4;
			static const unsigned int MaxIndices = MaxQuads * 6;
			static const unsigned int MaxTextureSlots = 32;

			unsigned int IndexCount = 0;
			QuadVertex* VertexBufferBase = nullptr;
			QuadVertex* VertexBufferPtr = nullptr;

			std::shared_ptr<VertexArray> VAO;
			std::shared_ptr<VertexBuffer> VBO;
			std::shared_ptr<Shader> Shader;

			std::array<std::shared_ptr<Texture>, MaxTextureSlots> TextureSlots;
			unsigned int TextureSlotsIndex = 1;
		};
		static Renderer2DData s_RenderData;
	};
}