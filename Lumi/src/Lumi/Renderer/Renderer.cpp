#include "pch.h"
#include "Renderer.h"

namespace Lumi
{
	std::shared_ptr<Renderer::SceneData> Renderer::s_SceneData =
		std::shared_ptr<Renderer::SceneData>(new Renderer::SceneData());
	
	void Renderer::Init()
	{
		RenderCommand::Init();
	}
	
	void Renderer::BeginScene(const Camera2D& camera)
	{
		s_SceneData->ProjectMatrix = camera.GetProjectMatrix();
		s_SceneData->ViewMatirx = camera.GetViewMatrix();
	}

	void Renderer::BeginScene(const Camera3D& camera)
	{

	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Draw(const std::shared_ptr<Shader>& shader, 
		const std::shared_ptr<VertexArray>& vertexArray)
	{
		shader->Use();

		shader->SetMat4("uProjection", s_SceneData->ProjectMatrix);
		shader->SetMat4("uView", s_SceneData->ViewMatirx);

		vertexArray->Bind();
		if (vertexArray->GetIndexBuffer())
		{
			RenderCommand::DrawIndex(vertexArray);
		}
		else
		{
			RenderCommand::DrawArray(vertexArray);
		}
		vertexArray->Unbind();
	}
}