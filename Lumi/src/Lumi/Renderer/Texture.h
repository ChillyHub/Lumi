#pragma once

namespace Lumi
{
	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void SetInternalFormat(unsigned int type) = 0;
		virtual void SetImageFormat(unsigned int type) = 0;
		virtual void SetWrapS(unsigned int type) = 0;
		virtual void SetWrapT(unsigned int type) = 0;
		virtual void SetFilterMin(unsigned int type) = 0;
		virtual void SetFilterMax(unsigned int type) = 0;

		virtual void Generate(unsigned int width, unsigned int height, unsigned char* data) = 0;
		virtual void Bind() const = 0;
		virtual void Bind(unsigned int slot) const = 0;
	};

	class Texture2D : public Texture
	{
	public:
		static std::shared_ptr<Texture2D> Create();
	};
}
