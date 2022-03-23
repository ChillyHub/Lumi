#include "pch.h"

#include "Renderer2D.h"

namespace Lumi
{
	std::unique_ptr<Renderer2D::Renderer2DStorage> Renderer2D::s_RenderData = 
		std::unique_ptr<Renderer2D::Renderer2DStorage>(new Renderer2D::Renderer2DStorage());
	
	void Renderer2D::Init()
	{
		LM_PROFILE_FUNCTION(); 
		
		float vertices[] = {
			// vertex           // coord
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		unsigned int indicesQ[] = {
			0, 1, 2,
			0, 2, 3
		};

		BufferLayout layoutQ = {
			{ "aPosition", ShaderDataType::Float3 },
			{ "aTexCoord", ShaderDataType::Float2 }
		};

		s_RenderData->VAO.reset(VertexArray::Create());

		std::shared_ptr<VertexBuffer> vertexBufferQ;
		vertexBufferQ.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		vertexBufferQ->SetLayout(layoutQ);
		s_RenderData->VAO->AddVertexBuffer(vertexBufferQ);

		std::shared_ptr<IndexBuffer> indexBufferQ;
		indexBufferQ.reset(IndexBuffer::Create(indicesQ, (unsigned int)std::size(indicesQ)));
		s_RenderData->VAO->AddIndexBuffer(indexBufferQ);

		vertexBufferQ->Unbind();
		s_RenderData->VAO->Unbind();

		s_RenderData->Shader = ResourceManager::GetShader("Shader2D");
		s_RenderData->Shader->Use();
		s_RenderData->Shader->SetInt("uTexture", 0);
	}

	void Renderer2D::BeginScene(const Camera2D& camera)
	{
		LM_PROFILE_FUNCTION(); 
		
		Renderer::BeginScene(camera);
	}

	void Renderer2D::EndScene()
	{
		LM_PROFILE_FUNCTION(); 
		
		Renderer::EndScene();
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size,
		const glm::vec3& color, float rotate)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, { color.r, color.g, color.b, 1.0f }, rotate);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size,
		const glm::vec4& color, float rotate)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, color, rotate);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size,
		const glm::vec3& color, float rotate)
	{
		DrawQuad(position, size, { color.r, color.g, color.b, 1.0f }, rotate);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size,
		const glm::vec4& color, float rotate)
	{
		LM_PROFILE_FUNCTION(); 
		
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, position);
		model = glm::rotate(model, glm::radians(rotate), { 0.0f, 0.0f, -1.0f });
		model = glm::scale(model, { size.x, size.y, 0.0f });

		s_RenderData->Shader->Use();
		s_RenderData->Shader->SetInt("uPng", false);
		s_RenderData->Shader->SetVec4("uColor", color);
		s_RenderData->Shader->SetMat4("uModel", model);

		Renderer::Draw(s_RenderData->Shader, s_RenderData->VAO);
	}

	void Renderer2D::DrawQuad(std::shared_ptr<Texture> texture, const glm::vec2& position,
		const glm::vec2& size, const glm::vec3& color, float rotate)
	{
		DrawQuad(texture, { position.x, position.y, 0.0f }, size,
			{ color.r, color.g, color.b, 1.0f }, rotate);
	}

	void Renderer2D::DrawQuad(std::shared_ptr<Texture> texture, const glm::vec2& position,
		const glm::vec2& size, const glm::vec4& color, float rotate)
	{
		DrawQuad(texture, { position.x, position.y, 0.0f }, size, color, rotate);
	}

	void Renderer2D::DrawQuad(std::shared_ptr<Texture> texture, const glm::vec3& position,
		const glm::vec2& size, const glm::vec3& color, float rotate)
	{
		DrawQuad(texture, position, size, { color.r, color.g, color.b, 1.0f }, rotate);
	}

	void Renderer2D::DrawQuad(std::shared_ptr<Texture> texture, const glm::vec3& position,
		const glm::vec2& size, const glm::vec4& color, float rotate)
	{
		LM_PROFILE_FUNCTION(); 
		
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, position);
		model = glm::rotate(model, glm::radians(rotate), { 0.0f, 0.0f, -1.0f });
		model = glm::scale(model, { size.x, size.y, 0.0f });

		s_RenderData->Shader->Use();
		s_RenderData->Shader->SetInt("uPng", true);
		s_RenderData->Shader->SetVec4("uColor", color);
		s_RenderData->Shader->SetMat4("uModel", model);

		texture->Bind();
		Renderer::Draw(s_RenderData->Shader, s_RenderData->VAO);
	}
}