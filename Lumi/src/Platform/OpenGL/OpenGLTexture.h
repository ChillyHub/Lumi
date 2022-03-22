#pragma once

#include "Lumi/Renderer/Texture.h"

namespace Lumi
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		// constructor and destructor
		OpenGLTexture2D();
		~OpenGLTexture2D();

		virtual unsigned int GetWidth() const override { return m_Width; }
		virtual unsigned int GetHeight() const override { return m_Height; }

		virtual void SetInternalFormat(unsigned int type) override { m_Internal_Format = type; }
		virtual void SetImageFormat(unsigned int type) override { m_Image_Format = type; }
		virtual void SetWrapS(unsigned int type) override { m_Wrap_S = type; }
		virtual void SetWrapT(unsigned int type) override { m_Wrap_T = type; }
		virtual void SetFilterMin(unsigned int type) override { m_Filter_Min = type; }
		virtual void SetFilterMax(unsigned int type) override { m_Filter_Max = type; }

		// generates texture from image
		virtual void Generate(unsigned int width, unsigned int height, unsigned char* data) override;
		// bind texture
		virtual void Bind() const override;
		virtual void Bind(unsigned int solt) const override;
	private:
		unsigned int m_TextureID;
		unsigned int m_Width, m_Height;
		unsigned int m_Internal_Format;
		unsigned int m_Image_Format;
		unsigned int m_Wrap_S;
		unsigned int m_Wrap_T;
		unsigned int m_Filter_Min;
		unsigned int m_Filter_Max;
	};
}
