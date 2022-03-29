#pragma once

#include "Lumi/Renderer/Texture.h"

namespace Lumi
{
	class OpenGLTexSpecCreator
	{
	public:
		static TextureSpecification Create(TextureType tp = TextureType::ColorMap,
			unsigned int width = 0, unsigned int height = 0);
	};
	
	class OpenGLTexture2D : public Texture2D
	{
	public:
		// constructor and destructor
		OpenGLTexture2D();
		~OpenGLTexture2D();

		virtual unsigned int GetTexID() const override { return m_TextureID; }
		virtual unsigned int GetWidth() const override { return m_TexSpec.Width; }
		virtual unsigned int GetHeight() const override { return m_TexSpec.Height; }
		virtual TextureSpecification GetSpec() const override { return m_TexSpec; }

		virtual void SetWidth(unsigned int width) override { m_TexSpec.Width = width; }
		virtual void SetHeight(unsigned int height) override { m_TexSpec.Height = height; }
		virtual void SetInternalFormat(unsigned int type) override { m_TexSpec.InternalFormat = type; }
		virtual void SetImageFormat(unsigned int type) override { m_TexSpec.ImageFormat = type; }
		virtual void SetWrapS(unsigned int type) override { m_TexSpec.WrapSFormat = type; }
		virtual void SetWrapT(unsigned int type) override { m_TexSpec.WrapTFormat = type; }
		virtual void SetFilterMin(unsigned int type) override { m_TexSpec.MinFilterFormat = type; }
		virtual void SetFilterMax(unsigned int type) override { m_TexSpec.MaxFilterFormat = type; }

		// generates texture from image
		virtual void Generate(unsigned int width, unsigned int height, unsigned char* data) override;
		virtual void Generate(const TextureSpecification& spec) override;
		// bind texture
		virtual void Bind() const override;
		virtual void Bind(unsigned int solt) const override;

		virtual bool operator==(const Texture& rhs) const override;
	private:
		unsigned int m_TextureID;
		TextureSpecification m_TexSpec;
	};
}
