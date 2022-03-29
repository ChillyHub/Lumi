#pragma once

#include "pch.h"

#include <glad/glad.h>

#include "Lumi/Events/Event.h"
#include "Lumi/Events/ApplicationEvent.h"
#include "Lumi/Renderer/Framebuffer.h"
#include "Lumi/Renderer/IFramebufferRenderer.h"
#include "Lumi/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLTexture.h"

namespace Lumi
{
	class OpenGLQuadFramebuffer : public QuadFramebuffer, public IFramebufferRenderer
	{
	public:
		OpenGLQuadFramebuffer(const FramebufferSpecification& spec);
		~OpenGLQuadFramebuffer();

		virtual unsigned int GetTexID(unsigned int index) const override;
		virtual TextureSpecification GetSpec(unsigned int index) override;
		virtual std::shared_ptr<Texture> GetTexture2D(unsigned int index) override;

		virtual void Bind() override;
		virtual void UnBind() override;

		virtual void OnEvent(Event& event) override;
		virtual bool OnResize(WindowResizeEvent& event) override;
		virtual void Resize(unsigned int width, unsigned int height) override;

		virtual unsigned int AddTexBuffer(const TextureSpecification& texspec) override;
	public:
		virtual void BeginFrameRender() override;
		virtual void EndFrameRender() override;

		virtual void DrawFrame(unsigned int index) override;
	private:
		void Init();
	private:
		unsigned int m_FBO = 0, m_RBO = 0;
		FramebufferSpecification m_Spec;
		Renderer2DData m_RenderData;
		std::vector<unsigned int> m_Textures;
		std::vector<std::shared_ptr<Texture>> m_TextureSlots;
		unsigned int m_TextureCount = 0;
	};

	//class OpenGLCubeFramebuffer : public CubeFramebuffer
	//{
	//public:
	//	OpenGLCubeFramebuffer(const FramebufferSpecification& spec);
	//	~OpenGLCubeFramebuffer();
	//private:
	//	void Init();
	//private:
	//	unsigned int m_FBO, m_RBO;
	//	FramebufferSpecification m_Spec;
	//	std::vector<unsigned int> m_Textures;
	//	std::unordered_map<unsigned int, std::shared_ptr<Texture2D>> m_Textures;
	//	unsigned int m_CubeCount = 0;
	//};
}