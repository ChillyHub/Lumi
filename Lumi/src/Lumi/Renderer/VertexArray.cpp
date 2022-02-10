#include "pch.h"
#include "VertexArray.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Lumi
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			LUMI_CORE_ASSERT(false, "RendererAPI: Unknown renderer API!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLVertexArray();
		case RendererAPI::API::Vulkan:
			LUMI_CORE_ASSERT(false, "RendererAPI: Vulkan currently not supported!");
			return nullptr;
		case RendererAPI::API::DirectX:
			LUMI_CORE_ASSERT(false, "RendererAPI: DirectX currently not supported!");
			return nullptr;
		default:
			break;
		}

		LUMI_CORE_ASSERT(false, "RendererAPI: Unknown renderer API!");
		return nullptr;
	}
}