#pragma once

#include "Lumi/Core/ResourceManager.h"

namespace Lumi
{
	class OpenGLResourceManager : public ResourceManager
	{
	public:
		// load and generate shader program, get shader
		static std::shared_ptr<Shader> LoadShader(const char* vShaderFile, const char* fShaderFile,
			const char* gShaderFile, std::string name);
		static std::shared_ptr<Shader> LoadShader(const std::string& vShaderFile, const std::string& fShaderFile,
			const std::string& gShaderFile, std::string name);
		// load and generate texture, get texture
		static std::shared_ptr<Texture> LoadTexture2D(const char* file, std::string name, 
			bool mipmap, bool gamma);
		static std::shared_ptr<Texture> LoadTexture2D(const std::string& file, std::string name, 
			bool mipmap, bool gamma);
	private:
		OpenGLResourceManager();
		~OpenGLResourceManager();
		// utility
		static std::shared_ptr<Shader> loadShaderFromFile(const char* vShaderFile, const char* fShaderFile,
			const char* gShaderFile = nullptr);
		static std::shared_ptr<Texture> loadTexture2DFromFile(const char* file, 
			bool mipmap = false, bool gamma = false);
	};
}
