#include "pch.h"

#include "OpenGLFramebuffer.h"

namespace Lumi
{
	OpenGLQuadFramebuffer::OpenGLQuadFramebuffer(const FramebufferSpecification& spec)
		: m_Spec(spec)
	{
		Init();
	}

	OpenGLQuadFramebuffer::~OpenGLQuadFramebuffer()
	{
		glDeleteFramebuffers(1, &m_FBO);
		glDeleteRenderbuffers(1, &m_RBO);
		glDeleteTextures((GLsizei)m_Textures.size(), m_Textures.data());
	}

	unsigned int OpenGLQuadFramebuffer::GetTexID(int index) const
	{
		if (index >= m_Textures.size())
		{
			LUMI_CORE_ASSERT(false, "ERROR: Out of range!");
		}
		return m_Textures[index];
	}

	std::shared_ptr<Texture2D> OpenGLQuadFramebuffer::GetTexture2D(unsigned int texID)
	{
		return m_TexturesSpec[texID];
	}

	TextureSpecification OpenGLQuadFramebuffer::GetSpec(unsigned int texID)
	{
		return m_TexturesSpec[texID]->GetSpec();
	}

	void OpenGLQuadFramebuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
	}

	void OpenGLQuadFramebuffer::UnBind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLQuadFramebuffer::Resize(unsigned int width, unsigned int height)
	{
		m_Spec.Width = width;
		m_Spec.Height = height;

		Init();
	}

	void OpenGLQuadFramebuffer::AddTexBuffer(const TextureSpecification& texspec)
	{
		auto spec = texspec;
		if (spec.Width == 0 && spec.Height == 0)
		{
			spec.Width = m_Spec.Width;
			spec.Height = m_Spec.Height;
		}
		glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
		auto texture = Texture2D::Create();
		texture->Generate(spec);
		texture->Bind();
		unsigned int texID = texture->GetTexID();
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + m_TextureCount,
			GL_TEXTURE_2D, texID, 0);
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			LUMI_CORE_ASSERT(false, "FRAMEBUFFER: Framebuffer not complete!");
		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		m_Textures.push_back(texID);
		m_TextureCount++;

		if (m_TexturesSpec.find(texID) == m_TexturesSpec.end())
		{
			m_TexturesSpec[texID] = texture;
		}
	}

	void OpenGLQuadFramebuffer::Init()
	{
		if (m_FBO)
		{
			glDeleteFramebuffers(1, &m_FBO);
			glDeleteRenderbuffers(1, &m_RBO);
			glDeleteTextures((GLsizei)m_Textures.size(), m_Textures.data());
			m_Textures.clear();
			m_TextureCount = 0;
		}
		
		glGenFramebuffers(1, &m_FBO);
		glGenRenderbuffers(1, &m_RBO);

		glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
		glBindRenderbuffer(GL_RENDERBUFFER, m_RBO);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, m_Spec.Width, m_Spec.Height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_RBO);
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			LUMI_CORE_ASSERT(false, "FRAMEBUFFER: Framebuffer not complete!");
		}

		for (auto& [_, spec] : m_TexturesSpec)
		{
			AddTexBuffer(spec->GetSpec());
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}
}