#pragma once

#include "pch.h"

#include "Lumi/Events/Event.h"
#include "Lumi/Events/ApplicationEvent.h"
#include "Lumi/Renderer/Texture.h"

namespace Lumi
{
	enum class FramebufferType
	{
		None = 0, 
		QuadTextureBuffer, 
		CubeTextureBuffer, 
		QuadHDRTextureBuffer, 
		CubeHDRTextureBuffer
	};
	
	struct FramebufferSpecification
	{
		unsigned int Width, Height;

		unsigned int Samples = 1;

		bool SwapChainTarget = false;
		FramebufferType type = FramebufferType::QuadTextureBuffer;
	};
	
	class Framebuffer
	{
	public:
		virtual ~Framebuffer() = default;

		virtual unsigned int GetTexID(unsigned int index) const = 0;
		virtual TextureSpecification GetSpec(unsigned int index) = 0;
		virtual std::shared_ptr<Texture> GetTexture2D(unsigned int index) = 0;

		virtual void Bind() = 0;
		virtual void UnBind() = 0;

		virtual void OnEvent(Event& event) = 0;
		virtual bool OnResize(WindowResizeEvent& event) = 0;
		virtual void Resize(unsigned int width, unsigned int height) = 0;

		virtual unsigned int AddTexBuffer(const TextureSpecification& texspec) = 0;

		static std::shared_ptr<Framebuffer> Create(const FramebufferSpecification& spec);
	};

	class QuadFramebuffer : public Framebuffer
	{
	public:
		virtual unsigned int GetTexID(unsigned int index) const = 0;
		virtual TextureSpecification GetSpec(unsigned int index) = 0;
		virtual std::shared_ptr<Texture> GetTexture2D(unsigned int index) = 0;

		virtual void Bind() = 0;
		virtual void UnBind() = 0;

		virtual void OnEvent(Event& event) = 0;
		virtual bool OnResize(WindowResizeEvent& event) = 0;
		virtual void Resize(unsigned int width, unsigned int height) = 0;

		virtual unsigned int AddTexBuffer(const TextureSpecification& texspec) = 0;

		static std::shared_ptr<Framebuffer> Create(const FramebufferSpecification& spec);
	};

	class CubeFramebuffer : public Framebuffer
	{
	public:
		virtual unsigned int GetTexID(unsigned int index) const = 0;
		virtual TextureSpecification GetSpec(unsigned int index) = 0;
		virtual std::shared_ptr<Texture> GetTexture2D(unsigned int index) = 0;

		virtual void Bind() = 0;
		virtual void UnBind() = 0;

		virtual void OnEvent(Event& event) = 0;
		virtual bool OnResize(WindowResizeEvent& event) = 0;
		virtual void Resize(unsigned int width, unsigned int height) = 0;

		virtual unsigned int AddTexBuffer(const TextureSpecification& texspec) = 0;

		static std::shared_ptr<Framebuffer> Create(const FramebufferSpecification& spec);
	};
}