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
		LM_PROFILE_FUNCTION();
		
		glDeleteFramebuffers(1, &m_FBO);
		glDeleteRenderbuffers(1, &m_RBO);
		glDeleteTextures((GLsizei)m_Textures.size(), m_Textures.data());
		Renderer2D::ResetFrameData();
	}

	unsigned int OpenGLQuadFramebuffer::GetTexID(unsigned int index) const
	{
		if (index >= m_Textures.size())
		{
			LUMI_CORE_ASSERT(false, "ERROR: Out of range!");
		}
		return m_Textures[index];
	}

	TextureSpecification OpenGLQuadFramebuffer::GetSpec(unsigned int index)
	{
		return m_TextureSlots[index]->GetSpec();
	}

	std::shared_ptr<Texture> OpenGLQuadFramebuffer::GetTexture2D(unsigned int index)
	{
		return m_TextureSlots[index];
	}

	void OpenGLQuadFramebuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
		glViewport(0, 0, m_Spec.Width, m_Spec.Height);
	}

	void OpenGLQuadFramebuffer::UnBind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLQuadFramebuffer::OnEvent(Event& event)
	{
		LM_PROFILE_FUNCTION();
		
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<Lumi::WindowResizeEvent>(BIND_EVENT_FN(OpenGLQuadFramebuffer::OnResize));
	}

	bool OpenGLQuadFramebuffer::OnResize(WindowResizeEvent& event)
	{
		LM_PROFILE_FUNCTION();
		
		Resize(event.GetWidth(), event.GetHeight());

		return false;
	}

	void OpenGLQuadFramebuffer::Resize(unsigned int width, unsigned int height)
	{
		LM_PROFILE_FUNCTION();
		
		m_Spec.Width = width;
		m_Spec.Height = height;

		if (width < 10000 && height < 10000 && width > 0 && height > 0)
		{
			Init();
		}
	}

	unsigned int OpenGLQuadFramebuffer::AddTexBuffer(const TextureSpecification& texspec)
	{
		LM_PROFILE_FUNCTION();
		
		auto spec = texspec;
		unsigned int oldID = spec.TextureID;
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

		for (unsigned int i = 0; i < m_TextureCount; i++)
		{
			if (m_Textures[i] == oldID)
			{
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i,
					GL_TEXTURE_2D, texID, 0);
				if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
				{
					LUMI_CORE_ASSERT(false, "FRAMEBUFFER: Framebuffer not complete!");
				}
				glBindFramebuffer(GL_FRAMEBUFFER, 0);
				m_Textures[i] = texID;
				m_TextureSlots[i] = texture;
				return i;
			}
		}

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + m_TextureCount,
			GL_TEXTURE_2D, texID, 0);
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			LUMI_CORE_ASSERT(false, "FRAMEBUFFER: Framebuffer not complete!");
		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		m_Textures.push_back(texID);
		m_TextureSlots.push_back(texture);

		return m_TextureCount++;
	}

	void OpenGLQuadFramebuffer::Init()
	{
		LM_PROFILE_FUNCTION();
		
		std::vector<unsigned int> texs;
		if (m_FBO)
		{
			glDeleteFramebuffers(1, &m_FBO);
			glDeleteRenderbuffers(1, &m_RBO);
			//glDeleteTextures((GLsizei)m_Textures.size(), m_Textures.data());
			Renderer2D::ResetFrameData();
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

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);

		unsigned int count = m_TextureCount;
		for (unsigned int i = 0; i < count; i++)
		{
			auto tex = m_TextureSlots[i];
			tex->SetWidth(m_Spec.Width);
			tex->SetHeight(m_Spec.Height);
			AddTexBuffer(tex->GetSpec());
		}
	}
}