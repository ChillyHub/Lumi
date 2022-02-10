#include "pch.h"
#include "Buffer.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Lumi
{
	/////////////////////////////////////////////////////////////////////
	// class VertexBuffer
	// ------------------

	VertexBuffer* VertexBuffer::Create(float* vertices, unsigned int count)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			LUMI_CORE_ASSERT(false, "RendererAPI: Unknown renderer API!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLVertexBuffer(vertices, count);
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

	/////////////////////////////////////////////////////////////////////
	// class IndexBuffer
	// -----------------

	IndexBuffer* IndexBuffer::Create(unsigned int* indices, unsigned int count)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			LUMI_CORE_ASSERT(false, "RendererAPI: Unknown renderer API!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLIndexBuffer(indices, count);
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