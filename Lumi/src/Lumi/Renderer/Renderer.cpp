#include "pch.h"
#include "Renderer.h"

namespace Lumi
{
	std::shared_ptr<Renderer::SceneData> Renderer::s_SceneData =
		std::shared_ptr<Renderer::SceneData>(new Renderer::SceneData());
	
	void Renderer::Init()
	{
		LM_PROFILE_FUNCTION(); 
		
		RenderCommand::Init();
	}

	void Renderer::BeginScene()
	{
		LM_PROFILE_FUNCTION();

		s_SceneData->ProjectMatrix = glm::mat4(1.0f);
		s_SceneData->ViewMatirx = glm::mat4(1.0f);
	}
	
	void Renderer::BeginScene(const Camera2D& camera)
	{
		LM_PROFILE_FUNCTION(); 
		
		s_SceneData->ProjectMatrix = camera.GetProjectMatrix();
		s_SceneData->ViewMatirx = camera.GetViewMatrix();
	}

	void Renderer::BeginScene(const Camera3D& camera)
	{
		LM_PROFILE_FUNCTION();
	}

	void Renderer::EndScene()
	{
		LM_PROFILE_FUNCTION();
	}

	void Renderer::Draw(const std::shared_ptr<Shader>& shader, 
		const std::shared_ptr<VertexArray>& vertexArray, unsigned int count)
	{
		LM_PROFILE_FUNCTION(); 
		
		shader->Use();

		shader->SetMat4("uProjection", s_SceneData->ProjectMatrix);
		shader->SetMat4("uView", s_SceneData->ViewMatirx);

		vertexArray->Bind();
		if (vertexArray->GetIndexBuffer())
		{
			RenderCommand::DrawIndex(vertexArray, count);
		}
		else
		{
			RenderCommand::DrawArray(vertexArray);
		}
		vertexArray->Unbind();
	}
}