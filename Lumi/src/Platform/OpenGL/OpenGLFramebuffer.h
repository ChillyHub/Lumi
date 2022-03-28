#pragma once

#include "pch.h"

#include <glad/glad.h>

#include "Lumi/Renderer/Framebuffer.h"

#include "Platform/OpenGL/OpenGLTexture.h"

namespace Lumi
{
	class OpenGLQuadFramebuffer : public QuadFramebuffer
	{
	public:
		OpenGLQuadFramebuffer(const FramebufferSpecification& spec);
		~OpenGLQuadFramebuffer();

		virtual unsigned int GetTexID(int index) const override;
		virtual TextureSpecification GetSpec(unsigned int texID) override;
		virtual std::shared_ptr<Texture2D> GetTexture2D(unsigned int texID) override;

		virtual void Bind() override;
		virtual void UnBind() override;

		virtual void Resize(unsigned int width, unsigned int height) override;

		virtual void AddTexBuffer(const TextureSpecification& texspec) override;
	private:
		void Init();
	private:
		unsigned int m_FBO, m_RBO;
		FramebufferSpecification m_Spec;
		std::vector<unsigned int> m_Textures;
		std::unordered_map<unsigned int, std::shared_ptr<Texture2D>> m_TexturesSpec;
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