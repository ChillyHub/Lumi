#include "pch.h"
#include "OpenGLResourceManager.h"

#include <stb_image.h>
#include <glad/glad.h>

namespace Lumi
{
	std::shared_ptr<Shader> OpenGLResourceManager::LoadShader(const char* vShaderFile, const char* fShaderFile,
		const char* gShaderFile, std::string name)
	{
		Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
		return Shaders[name];
	}

	std::shared_ptr<Shader> OpenGLResourceManager::LoadShader(const std::string& vShaderFile,
		const std::string& fShaderFile, const std::string& gShaderFile, std::string name)
	{
		Shaders[name] = loadShaderFromFile(vShaderFile.c_str(), fShaderFile.c_str(), gShaderFile.c_str());
		return Shaders[name];
	}

	std::shared_ptr<Texture> OpenGLResourceManager::LoadTexture2D(const char* file, bool alpha, std::string name)
	{
		Textures[name] = loadTexture2DFromFile(file, alpha);
		return Textures[name];
	}

	std::shared_ptr<Texture> OpenGLResourceManager::LoadTexture2D(const std::string& file, bool alpha, std::string name)
	{
		Textures[name] = loadTexture2DFromFile(file.c_str(), alpha);
		return Textures[name];
	}

	OpenGLResourceManager::OpenGLResourceManager()
	{

	}

	OpenGLResourceManager::~OpenGLResourceManager()
	{

	}

	std::shared_ptr<Shader> OpenGLResourceManager::loadShaderFromFile
	(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile)
	{
		// 1. retrieve the vertex/fragment source code from filePath
		std::string vertexCode;
		std::string fragmnetCode;
		std::string geometryCode;
		try
		{
			// open files
			std::ifstream vertexShaderFile(vShaderFile);
			std::ifstream fragmentShaderFile(fShaderFile);
			std::stringstream vShaderStream, fShaderStream;
			// read file's buffer contents into streams
			vShaderStream << vertexShaderFile.rdbuf();
			fShaderStream << fragmentShaderFile.rdbuf();
			// close file handlers
			vertexShaderFile.close();
			fragmentShaderFile.close();
			// convert stream into string
			vertexCode = vShaderStream.str();
			fragmnetCode = fShaderStream.str();

			if (vertexCode.empty() || fragmnetCode.empty())
			{
				throw std::exception("Empty shader file.");
			}

			// load geometry shader
			if (gShaderFile != nullptr)
			{
				std::ifstream geometryShaderFile(gShaderFile);
				std::stringstream gShaderStream;
				gShaderStream << geometryShaderFile.rdbuf();
				geometryShaderFile.close();
				geometryCode = gShaderStream.str();
			}
		}
		catch (const std::exception& e)
		{
			LUMI_CORE_WARN("{0}", e.what());
			LUMI_CORE_ASSERT(false, "ERROR::SHADER: Filed to read shader file");
		}

		// 2. create shader object from source code
		return Shader::Create(vertexCode, fragmnetCode, geometryCode);
	}

	std::shared_ptr<Texture> OpenGLResourceManager::loadTexture2DFromFile(const char* file, bool alpha)
	{
#       ifdef _LM_WINDOWS_
		stbi_set_flip_vertically_on_load(1);
#       endif

		// create texture object
		std::shared_ptr<Texture> texture = Texture2D::Create();
		if (alpha)
		{
			texture->SetInternalFormat(GL_RGBA);
			texture->SetImageFormat(GL_RGBA);
		}
		// load image
		int width, height, nrChannels;
		unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);
		// generate texture
		if (data)
			texture->Generate(width, height, data);
		else
			LUMI_CORE_ASSERT(false, "ERROR::TEXTURE: Filed to read texture file");
		// free image data
		stbi_image_free(data);
		return texture;
	}
}