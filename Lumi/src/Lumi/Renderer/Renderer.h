#pragma once

#include "RenderCommand.h"
#include "Shader.h"

#include "Lumi/Scene/Camera.h"
#include "Lumi/Scene/Camera2D.h"
#include "Lumi/Scene/Camera3D.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Lumi
{	
	class Renderer
	{
	public:
		static void Init();

		static void BeginScene();
		static void BeginScene(const Camera2D& camera);
		static void BeginScene(const Camera3D& camera);
		static void EndScene();

		static void Draw(const std::shared_ptr<Shader>& shader, 
			const std::shared_ptr<VertexArray>& vertexArray, unsigned int count = 0);

		static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData
		{
			glm::mat4 ProjectMatrix = glm::mat4(1.0f);
			glm::mat4 ViewMatirx    = glm::mat4(1.0f);
		};

		static std::shared_ptr<SceneData> s_SceneData;
	};
}
