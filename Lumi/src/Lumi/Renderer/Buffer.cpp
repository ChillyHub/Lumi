#include "pch.h"
#include "Buffer.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Lumi
{
	/////////////////////////////////////////////////////////////////////
	// class VertexBuffer
	// ------------------

	std::shared_ptr<VertexBuffer> VertexBuffer::Create(unsigned int count)
	{
		LM_PROFILE_FUNCTION();

		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			LUMI_CORE_ASSERT(false, "RendererAPI: Unknown renderer API!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::shared_ptr<VertexBuffer>(new OpenGLVertexBuffer(count));
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

	std::shared_ptr<VertexBuffer> VertexBuffer::Create(float* vertices, unsigned int count)
	{
		LM_PROFILE_FUNCTION(); 
		
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			LUMI_CORE_ASSERT(false, "RendererAPI: Unknown renderer API!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::shared_ptr<VertexBuffer>(new OpenGLVertexBuffer(vertices, count));
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

	std::shared_ptr<IndexBuffer> IndexBuffer::Create(unsigned int* indices, unsigned int count)
	{
		LM_PROFILE_FUNCTION(); 
		
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			LUMI_CORE_ASSERT(false, "RendererAPI: Unknown renderer API!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::shared_ptr<IndexBuffer>(new OpenGLIndexBuffer(indices, count));
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