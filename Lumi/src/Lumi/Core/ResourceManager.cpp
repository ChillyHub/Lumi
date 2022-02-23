#include "pch.h"
#include "ResourceManager.h"

#include "Platform/OpenGL/OpenGLResourceManager.h"

namespace Lumi
{
	// Instantiate static variables
	std::map<std::string, std::shared_ptr<Shader>> ResourceManager::Shaders;
	std::map<std::string, std::shared_ptr<Texture>> ResourceManager::Textures;

#ifdef _LM_WINDOWS_

	std::shared_ptr<Shader> ResourceManager::LoadShader(const char* vShaderFile, const char* fShaderFile,
		const char* gShaderFile, std::string name)
	{
		return OpenGLResourceManager::LoadShader(vShaderFile, fShaderFile, gShaderFile, name);
	}

	std::shared_ptr<Shader> ResourceManager::LoadShader(const std::string& vShaderFile, 
		const std::string& fShaderFile, const std::string& gShaderFile, std::string name)
	{
		return OpenGLResourceManager::LoadShader(vShaderFile, fShaderFile, gShaderFile, name);
	}

	std::shared_ptr<Shader> ResourceManager::GetShader(std::string name)
	{
		return Shaders[name];
	}

	std::shared_ptr<Texture> ResourceManager::LoadTexture2D(const char* file, bool alpha, std::string name)
	{
		return OpenGLResourceManager::LoadTexture2D(file, alpha, name);
	}

	std::shared_ptr<Texture> ResourceManager::LoadTexture2D(const std::string& file, bool alpha, std::string name)
	{
		return OpenGLResourceManager::LoadTexture2D(file, alpha, name);
	}

	std::shared_ptr<Texture> ResourceManager::GetTexture2D(std::string name)
	{
		return Textures[name];
	}
#endif

	void ResourceManager::Clear()
	{
		for (auto& [_, shader] : Shaders)
			shader->~Shader();
		for (auto& [_, texture] : Textures)
			texture->~Texture();
	}
}