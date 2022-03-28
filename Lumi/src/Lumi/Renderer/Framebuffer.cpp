#include "pch.h"

#include "Framebuffer.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLFramebuffer.h"

namespace Lumi
{
	std::shared_ptr<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec)
	{
		if (spec.type == FramebufferType::QuadTextureBuffer || 
			spec.type == FramebufferType::QuadHDRTextureBuffer)
		{
			return QuadFramebuffer::Create(spec);
		}
		if (spec.type == FramebufferType::CubeTextureBuffer ||
			spec.type == FramebufferType::CubeHDRTextureBuffer)
		{
			return CubeFramebuffer::Create(spec);
		}
		LUMI_CORE_ASSERT(false, "Framebuffer: Unknown framebuffer type!");
		return nullptr;
	}

	std::shared_ptr<Framebuffer> QuadFramebuffer::Create(const FramebufferSpecification& spec)
	{
		LM_PROFILE_FUNCTION();

		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			LUMI_CORE_ASSERT(false, "RendererAPI: Unknown renderer API!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLQuadFramebuffer>(spec);
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

	std::shared_ptr<Framebuffer> CubeFramebuffer::Create(const FramebufferSpecification& spec)
	{
		LM_PROFILE_FUNCTION();

		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			LUMI_CORE_ASSERT(false, "RendererAPI: Unknown renderer API!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return nullptr;// std::make_shared<OpenGLCubeFramebuffer>(spec);
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