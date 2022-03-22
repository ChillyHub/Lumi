#pragma once

#include "Lumi/Renderer/Shader.h"
#include "Lumi/Renderer/Texture.h"

namespace Lumi
{
	class ResourceManager
	{
	public:
		// load and generate shader program, get shader
		static std::shared_ptr<Shader> LoadShader(const char* vShaderFile, const char* fShaderFile, 
			const char* gShaderFile, std::string name);
		static std::shared_ptr<Shader> LoadShader(const std::string& vShaderFile, const std::string& fShaderFile,
			const std::string& gShaderFile, std::string name);
		static std::shared_ptr<Shader> GetShader(std::string name);
		// load and generate texture, get texture
		static std::shared_ptr<Texture> LoadTexture2D(const char* file, std::string name, 
			bool mipmap = false, bool gamma = false);
		static std::shared_ptr<Texture> LoadTexture2D(const std::string& file, std::string name, 
			bool mipmap = false, bool gamma = false);
		static std::shared_ptr<Texture> GetTexture2D(std::string name);
		// de-allocates all loaded resources
		static void Clear();
	protected:
		// resource storage
		static std::map<std::string, std::shared_ptr<Shader>> Shaders;
		static std::map<std::string, std::shared_ptr<Texture>> Textures;
	};
}
