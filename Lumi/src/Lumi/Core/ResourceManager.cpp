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
		LM_PROFILE_FUNCTION();
		
		return OpenGLResourceManager::LoadShader(vShaderFile, fShaderFile, gShaderFile, name);
	}

	std::shared_ptr<Shader> ResourceManager::LoadShader(const std::string& vShaderFile, 
		const std::string& fShaderFile, const std::string& gShaderFile, std::string name)
	{
		LM_PROFILE_FUNCTION();
		
		return OpenGLResourceManager::LoadShader(vShaderFile, fShaderFile, gShaderFile, name);
	}

	std::shared_ptr<Shader> ResourceManager::GetShader(std::string name)
	{
		LM_PROFILE_FUNCTION(); 
		
		return Shaders[name];
	}

	std::shared_ptr<Texture> ResourceManager::LoadTexture2D(const char* file, std::string name, 
		bool mipmap, bool gamma)
	{
		LM_PROFILE_FUNCTION(); 
		
		return OpenGLResourceManager::LoadTexture2D(file, name, mipmap, gamma);
	}

	std::shared_ptr<Texture> ResourceManager::LoadTexture2D(const std::string& file, std::string name, 
		bool mipmap, bool gamma)
	{
		LM_PROFILE_FUNCTION(); 
		
		return OpenGLResourceManager::LoadTexture2D(file, name, mipmap, gamma);
	}

	std::shared_ptr<Texture> ResourceManager::GetTexture2D(std::string name)
	{
		LM_PROFILE_FUNCTION(); 
		
		return Textures[name];
	}
#endif

	void ResourceManager::Clear()
	{
		LM_PROFILE_FUNCTION();
		
		for (auto& [_, shader] : Shaders)
			shader->~Shader();
		for (auto& [_, texture] : Textures)
			texture->~Texture();
	}
}