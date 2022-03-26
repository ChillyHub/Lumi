#include "pch.h"

#include "Renderer2D.h"

namespace Lumi
{	
	Renderer2D::Renderer2DData Renderer2D::s_RenderData = Renderer2D::Renderer2DData();
	
	void Renderer2D::Init()
	{
		LM_PROFILE_FUNCTION();

		BufferLayout layout = {
			{ "aPosition", ShaderDataType::Float3 },
			{ "aTexCoord", ShaderDataType::Float2 }, 
			{ "aColor",    ShaderDataType::Float4 }, 
			{ "aTexIndex", ShaderDataType::Float  }
		};

		s_RenderData.VAO = VertexArray::Create();
		s_RenderData.VBO = VertexBuffer::Create(s_RenderData.MaxVertices * sizeof(QuadVertex));
		s_RenderData.VBO->SetLayout(layout);
		s_RenderData.VAO->AddVertexBuffer(s_RenderData.VBO);

		unsigned int* indices = new unsigned int[s_RenderData.MaxIndices];
		s_RenderData.VertexBufferBase = new QuadVertex[s_RenderData.MaxIndices];
		for (unsigned int i = 0, offset = 0; i < s_RenderData.MaxIndices; i += 6, offset += 4)
		{
			indices[i + 0u] = offset + 0u;
			indices[i + 1u] = offset + 1u;
			indices[i + 2u] = offset + 3u;

			indices[i + 3u] = offset + 1u;
			indices[i + 4u] = offset + 2u;
			indices[i + 5u] = offset + 3u;
		}

		auto indexBufferQ = IndexBuffer::Create(indices, s_RenderData.MaxVertices);
		s_RenderData.VAO->AddIndexBuffer(indexBufferQ);

		delete[] indices;

		s_RenderData.VBO->Unbind();
		s_RenderData.VAO->Unbind();

		unsigned int whiteTextureData = 0xffffffff;
		s_RenderData.TextureSlots[0] = Texture2D::Create();
		s_RenderData.TextureSlots[0]->Generate(1, 1, (unsigned char*)&whiteTextureData);

		int sample[s_RenderData.MaxTextureSlots];
		for (int i = 0; i < s_RenderData.MaxTextureSlots; i++)
		{
			sample[i] = i;
		}

		ResourceManager::LoadShader("../Lumi/include/innerAssets/shaders/shaderQuad.vert",
			"../Lumi/include/innerAssets/shaders/shaderQuad.frag", nullptr, "QuadShader");
		s_RenderData.Shader = ResourceManager::GetShader("QuadShader");
		s_RenderData.Shader->Use();
		s_RenderData.Shader->SetIntV("uTextures", sample, s_RenderData.MaxTextureSlots);
	}

	void Renderer2D::BeginScene(const Camera2D& camera)
	{
		LM_PROFILE_FUNCTION(); 

		s_RenderData.IndexCount = 0u;
		s_RenderData.VertexBufferPtr = s_RenderData.VertexBufferBase;

		s_RenderData.TextureSlotsIndex = 1u;

		Renderer::BeginScene(camera);
	}

	void Renderer2D::EndScene()
	{
		LM_PROFILE_FUNCTION(); 
		
		unsigned int dataSize = (uint8_t*)s_RenderData.VertexBufferPtr
			- (uint8_t*)s_RenderData.VertexBufferBase;
		s_RenderData.VBO->SetData(s_RenderData.VertexBufferBase, dataSize);
		Flush();

		Renderer::EndScene();
	}

	void Renderer2D::Flush()
	{
		LM_PROFILE_FUNCTION();

		for (unsigned int i = 0u; i < s_RenderData.TextureSlotsIndex; i++)
		{
			s_RenderData.TextureSlots[i]->Bind(i);
		}
		
		Renderer::Draw(s_RenderData.Shader, s_RenderData.VAO, s_RenderData.IndexCount);
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

		s_RenderData.VertexBufferPtr->Position = position;
		s_RenderData.VertexBufferPtr->TexCoord = { 0.0f, 0.0f };
		s_RenderData.VertexBufferPtr->Color = color;
		s_RenderData.VertexBufferPtr->TexIndex = 0.0f;
		s_RenderData.VertexBufferPtr++;

		s_RenderData.VertexBufferPtr->Position = { position.x + size.x, position.y, position.z };
		s_RenderData.VertexBufferPtr->TexCoord = { 1.0f, 0.0f };
		s_RenderData.VertexBufferPtr->Color = color;
		s_RenderData.VertexBufferPtr->TexIndex = 0.0f;
		s_RenderData.VertexBufferPtr++;

		s_RenderData.VertexBufferPtr->Position = { position.x + size.x, position.y + size.y, position.z };
		s_RenderData.VertexBufferPtr->TexCoord = { 1.0f, 1.0f };
		s_RenderData.VertexBufferPtr->Color = color;
		s_RenderData.VertexBufferPtr->TexIndex = 0.0f;
		s_RenderData.VertexBufferPtr++;

		s_RenderData.VertexBufferPtr->Position = { position.x, position.y + size.y, position.z };
		s_RenderData.VertexBufferPtr->TexCoord = { 0.0f, 1.0f };
		s_RenderData.VertexBufferPtr->Color = color;
		s_RenderData.VertexBufferPtr->TexIndex = 0.0f;
		s_RenderData.VertexBufferPtr++;

		s_RenderData.IndexCount += 6;
		
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(rotate), { 0.0f, 0.0f, -1.0f });

		s_RenderData.Shader->Use();
		s_RenderData.Shader->SetMat4("uModel", model);

		//Renderer::Draw(s_RenderData.Shader, s_RenderData.VAO);
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

		unsigned int textureIndex = 0u;
		for (unsigned int i = 1; i < s_RenderData.TextureSlotsIndex; i++)
		{
			if (*s_RenderData.TextureSlots[i].get() == *texture.get())
			{
				textureIndex = i;
				break;
			}
		}

		if (textureIndex == 0)
		{
			textureIndex = s_RenderData.TextureSlotsIndex;
			s_RenderData.TextureSlots[s_RenderData.TextureSlotsIndex++] = texture;
		}

		s_RenderData.VertexBufferPtr->Position = position;
		s_RenderData.VertexBufferPtr->TexCoord = { 0.0f, 0.0f };
		s_RenderData.VertexBufferPtr->Color = color;
		s_RenderData.VertexBufferPtr->TexIndex = (float)textureIndex;
		s_RenderData.VertexBufferPtr++;

		s_RenderData.VertexBufferPtr->Position = { position.x + size.x, position.y, position.z };
		s_RenderData.VertexBufferPtr->TexCoord = { 1.0f, 0.0f };
		s_RenderData.VertexBufferPtr->Color = color;
		s_RenderData.VertexBufferPtr->TexIndex = (float)textureIndex;
		s_RenderData.VertexBufferPtr++;

		s_RenderData.VertexBufferPtr->Position = { position.x + size.x, position.y + size.y, position.z };
		s_RenderData.VertexBufferPtr->TexCoord = { 1.0f, 1.0f };
		s_RenderData.VertexBufferPtr->Color = color;
		s_RenderData.VertexBufferPtr->TexIndex = (float)textureIndex;
		s_RenderData.VertexBufferPtr++;

		s_RenderData.VertexBufferPtr->Position = { position.x, position.y + size.y, position.z };
		s_RenderData.VertexBufferPtr->TexCoord = { 0.0f, 1.0f };
		s_RenderData.VertexBufferPtr->Color = color;
		s_RenderData.VertexBufferPtr->TexIndex = (float)textureIndex;
		s_RenderData.VertexBufferPtr++;

		s_RenderData.IndexCount += 6;
		
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(rotate), { 0.0f, 0.0f, -1.0f });
		
		s_RenderData.Shader->Use();
		s_RenderData.Shader->SetMat4("uModel", model);
	}
}