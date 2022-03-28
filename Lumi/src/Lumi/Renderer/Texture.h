#pragma once

namespace Lumi
{
	enum class TextureType
	{
		None = 0,
		DepthMap,
		ColorMap,
		NormalMap,
		AlbedoMap,
		ShadowMap,
		PositionMap,
		LightingMap,
		CustomizeMap
	};

	struct TextureSpecification
	{
		unsigned int TextureID;
		unsigned int Width, Height;

		unsigned int InternalFormat;
		unsigned int ImageFormat;
		unsigned int WrapSFormat;
		unsigned int WrapTFormat;
		unsigned int WrapRFormat;
		unsigned int MinFilterFormat;
		unsigned int MaxFilterFormat;

		TextureType type = TextureType::ColorMap;
	};

	class TexSpecCreator
	{
	public:
		static TextureSpecification Create(TextureType tp = TextureType::ColorMap,
			unsigned int width = 0, unsigned int height = 0);
	};
	
	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual unsigned int GetTexID() const = 0;
		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;
		virtual TextureSpecification GetSpec() const = 0;

		virtual void SetInternalFormat(unsigned int type) = 0;
		virtual void SetImageFormat(unsigned int type) = 0;
		virtual void SetWrapS(unsigned int type) = 0;
		virtual void SetWrapT(unsigned int type) = 0;
		virtual void SetFilterMin(unsigned int type) = 0;
		virtual void SetFilterMax(unsigned int type) = 0;

		virtual void Generate(unsigned int width, unsigned int height, unsigned char* data) = 0;
		virtual void Generate(const TextureSpecification& spec) = 0;
		virtual void Bind() const = 0;
		virtual void Bind(unsigned int slot) const = 0;

		virtual bool operator==(const Texture& rhs) const = 0;
	};

	class Texture2D : public Texture
	{
	public:
		static std::shared_ptr<Texture2D> Create();
	};
}
