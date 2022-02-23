#include "pch.h"
#include "Texture.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLTexture.h"

namespace Lumi
{
	std::shared_ptr<Texture2D> Texture2D::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			LUMI_CORE_ASSERT(false, "RendererAPI: Unknown renderer API!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLTexture2D>();
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