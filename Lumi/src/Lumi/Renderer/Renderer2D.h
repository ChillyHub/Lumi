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
		struct Renderer2DStorage
		{
			std::shared_ptr<VertexArray> VAO;
			std::shared_ptr<Shader> Shader;
		};
		static std::unique_ptr<Renderer2DStorage> s_RenderData;
	};
}