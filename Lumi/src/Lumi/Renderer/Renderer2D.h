#pragma once

#include "RenderCommand.h"
#include "Renderer.h"
#include "Shader.h"

#include "Lumi/Core/ResourceManager.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Lumi
{
	class Renderer2D
	{
	public:
		struct Stat
		{
			unsigned int DrawCall = 0;
			unsigned int QuadCount = 0;

			unsigned int GetVerteicesCount() { return QuadCount * 4; };
			unsigned int GetIndicesCount() { return QuadCount * 6; };
		};
	public:
		static void Init(bool initFramebuffer = false);

		static void BeginScene();
		//static void BeginScene(const Camera2D& camera);
		static void BeginScene(const Camera& camera);
		static void ReBeginScene();
		static void EndScene();

		static void BeginFrame();
		static void ReBeginFrame();
		static void EndFrame();

		static void Flush();
		static void FlushFrame();

		static void ResetFrameData();

		static Stat GetStats();
		static void ResetStats();

		static void DrawQuad(const glm::vec2& position = glm::vec2(0.0f),
			const glm::vec2& size = glm::vec2(1.0f),
			const glm::vec3& color = glm::vec3(1.0f), 
			const glm::quat& rotate = glm::quat(1.0f, 0.0f, 0.0f, 0.0f));
		static void DrawQuad(const glm::vec2& position,
			const glm::vec2& size,
			const glm::vec4& color, 
			const glm::quat& rotate = glm::quat(1.0f, 0.0f, 0.0f, 0.0f));
		static void DrawQuad(const glm::vec3& position,
			const glm::vec2& size = glm::vec2(1.0f),
			const glm::vec3& color = glm::vec3(1.0f), 
			const glm::quat& rotate = glm::quat(1.0f, 0.0f, 0.0f, 0.0f));
		static void DrawQuad(const glm::vec3& position,
			const glm::vec2& size,
			const glm::vec4& color, 
			const glm::quat& rotate = glm::quat(1.0f, 0.0f, 0.0f, 0.0f));
		static void DrawQuad(std::shared_ptr<Texture> texture, 
			const glm::vec2& position = glm::vec2(0.0f),
			const glm::vec2& size = glm::vec2(1.0f),
			const glm::vec3& color = glm::vec3(1.0f), 
			const glm::quat& rotate = glm::quat(1.0f, 0.0f, 0.0f, 0.0f));
		static void DrawQuad(std::shared_ptr<Texture> texture, 
			const glm::vec2& position,
			const glm::vec2& size,
			const glm::vec4& color, 
			const glm::quat& rotate = glm::quat(1.0f, 0.0f, 0.0f, 0.0f));
		static void DrawQuad(std::shared_ptr<Texture> texture, 
			const glm::vec3& position,
			const glm::vec2& size = glm::vec2(1.0f),
			const glm::vec3& color = glm::vec3(1.0f), 
			const glm::quat& rotate = glm::quat(1.0f, 0.0f, 0.0f, 0.0f));
		static void DrawQuad(std::shared_ptr<Texture> texture, 
			const glm::vec3& position,
			const glm::vec2& size,
			const glm::vec4& color, 
			const glm::quat& rotate = glm::quat(1.0f, 0.0f, 0.0f, 0.0f));

		static void DrawFrame(std::shared_ptr<Texture> texture);
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

			glm::vec4 QuadVertexPositions[4] = {
				{ -0.5f, -0.5f, 0.0f, 1.0f },
				{  0.5f, -0.5f, 0.0f, 1.0f },
				{  0.5f,  0.5f, 0.0f, 1.0f },
				{ -0.5f,  0.5f, 0.0f, 1.0f }
			};

			Stat Stats;
		};
		static Renderer2DData s_RenderData;

		struct FramebufferData
		{
			static const unsigned int MaxQuads = 10;
			static const unsigned int MaxVertices = MaxQuads * 4;
			static const unsigned int MaxIndices = MaxQuads * 6;
			static const unsigned int MaxTextureSlots = 8;
			
			unsigned int IndexCount = 0;
			QuadVertex* VertexBufferBase = nullptr;
			QuadVertex* VertexBufferPtr = nullptr;

			std::shared_ptr<VertexArray> VAO;
			std::shared_ptr<VertexBuffer> VBO;
			std::shared_ptr<Shader> Shader;

			std::array<std::shared_ptr<Texture>, MaxTextureSlots> TextureSlots;
			unsigned int TextureSlotsIndex = 0;

			glm::vec4 QuadVertexPositions[4] = {
				{ -1.0f, -1.0f, 0.0f, 1.0f },
				{  1.0f, -1.0f, 0.0f, 1.0f },
				{  1.0f,  1.0f, 0.0f, 1.0f },
				{ -1.0f,  1.0f, 0.0f, 1.0f }
			};
		};
		static FramebufferData s_FramebufferData;
	};
}