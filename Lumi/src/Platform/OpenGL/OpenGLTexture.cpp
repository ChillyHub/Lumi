#include "pch.h"
#include "OpenGLTexture.h"

#include <glad/glad.h>

namespace Lumi
{
	TextureSpecification OpenGLTexSpecCreator::Create(TextureType tp,
		unsigned int width, unsigned int height)
	{
		TextureSpecification spec;

		spec.Width = width;
		spec.Height = height;
		spec.WrapSFormat = GL_CLAMP_TO_EDGE;
		spec.WrapTFormat = GL_CLAMP_TO_EDGE;
		spec.WrapRFormat = GL_CLAMP_TO_EDGE;
		spec.MinFilterFormat = GL_NEAREST;
		spec.MaxFilterFormat = GL_NEAREST;

		switch (tp)
		{
		case TextureType::None:
			return spec;
		case TextureType::DepthMap:
			spec.InternalFormat = GL_DEPTH24_STENCIL8;
			spec.ImageFormat = GL_FLOAT;
			return spec;
		case TextureType::ColorMap:
			spec.InternalFormat = GL_RGBA;
			spec.ImageFormat = GL_RGBA;
			spec.MinFilterFormat = GL_LINEAR;
			spec.MaxFilterFormat = GL_LINEAR;
			return spec;
		case TextureType::NormalMap:
			spec.InternalFormat = GL_RGB16F;
			spec.ImageFormat = GL_RGB;
			return spec;
		case TextureType::AlbedoMap:
			spec.InternalFormat = GL_RGBA;
			spec.ImageFormat = GL_RGBA;
			return spec;
		case TextureType::ShadowMap:
			spec.InternalFormat = GL_RGB16F;
			spec.ImageFormat = GL_RED;
			return spec;
		case TextureType::PositionMap:
			spec.InternalFormat = GL_RGB16F;
			spec.ImageFormat = GL_RGB;
			return spec;
		case TextureType::LightingMap:
			spec.InternalFormat = GL_RGB16F;
			spec.ImageFormat = GL_RGB;
			spec.MinFilterFormat = GL_LINEAR;
			spec.MaxFilterFormat = GL_LINEAR;
			return spec;
		case TextureType::CustomizeMap:
			return spec;
		default:
			break;
		}
		return spec;
	}
	
	OpenGLTexture2D::OpenGLTexture2D()
	{
		glGenTextures(1, &m_TextureID);

		m_TexSpec = TexSpecCreator::Create();
		m_TexSpec.TextureID = m_TextureID;
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_TextureID);
	}

	void OpenGLTexture2D::Generate(unsigned int width, unsigned int height, unsigned char* data)
	{
		LM_PROFILE_FUNCTION(); 
		
		m_TexSpec.Width = width;
		m_TexSpec.Height = height;
		// crete texture
		glBindTexture(GL_TEXTURE_2D, m_TextureID);
		glTexImage2D(GL_TEXTURE_2D, 0, m_TexSpec.InternalFormat, width, height, 
			0, m_TexSpec.ImageFormat, GL_UNSIGNED_BYTE, data);
		if (m_TexSpec.MinFilterFormat == GL_LINEAR_MIPMAP_LINEAR)
		{
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		// set texture wrap and filter modes
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_TexSpec.WrapSFormat);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_TexSpec.WrapTFormat);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_TexSpec.MinFilterFormat);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_TexSpec.MaxFilterFormat);
		// unbind texture
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void OpenGLTexture2D::Generate(const TextureSpecification& spec)
	{
		LM_PROFILE_FUNCTION();
		
		m_TexSpec = spec;
		glBindTexture(GL_TEXTURE_2D, m_TextureID);
		glTexImage2D(GL_TEXTURE_2D, 0, spec.InternalFormat, spec.Width, spec.Height,
			0, spec.ImageFormat, GL_FLOAT, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, spec.WrapSFormat);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, spec.WrapTFormat);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, spec.MinFilterFormat);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, spec.MaxFilterFormat);

		glBindTexture(GL_TEXTURE_2D, 0);
		m_TexSpec.TextureID = m_TextureID;
	}

	void OpenGLTexture2D::Bind() const
	{
		glBindTexture(GL_TEXTURE_2D, m_TextureID);
	}

	void OpenGLTexture2D::Bind(unsigned int slot) const
	{
		glBindTextureUnit(slot, m_TextureID);
	}

	bool OpenGLTexture2D::operator==(const Texture& rhs) const
	{
		return this->m_TextureID == ((OpenGLTexture2D&)rhs).m_TextureID;
	}
}