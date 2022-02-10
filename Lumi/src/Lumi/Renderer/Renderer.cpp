#include "pch.h"
#include "Renderer.h"

namespace Lumi
{
	void Renderer::BeginScene()
	{

	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
	{
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