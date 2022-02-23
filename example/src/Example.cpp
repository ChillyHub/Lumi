#include <Lumi.h>

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui.h>

// tmp
#include "Platform/OpenGL/OpenGLShader.h"
#include <memory>
#include <filesystem>

class ExampleLayer : public Lumi::Layer
{
public:
	ExampleLayer(int width, int height) : Layer("Example")
	{
		////////////////////////////////////////////////////////////////////
		// A TESTING TRIANGLE
		// 
		m_Camera = Lumi::Camera2D(width, height, { 0.0f, 0.0f, 2.0f });

		std::string currentPath = std::filesystem::current_path().string();

		Lumi::ResourceManager::LoadShader
		(currentPath + "\\shaders\\shaderT.vert", currentPath + "\\shaders\\shaderT.frag", 
			std::string(), "TriangleShader");

		Lumi::ResourceManager::LoadShader
		(currentPath + "\\shaders\\shaderQ.vert", currentPath + "\\shaders\\shaderQ.frag", 
			std::string(), "QuadShader");

		Lumi::ResourceManager::LoadTexture2D
		(currentPath + "\\assets\\textures\\barbara2.png", true, "Barbara");

		float verticesT[] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
			 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
		};

		unsigned int indicesT[] = {
			0, 1, 2
		};

		Lumi::BufferLayout layoutT = {
			{ "aPosition", Lumi::ShaderDataType::Float3 },
			{ "aColor", Lumi::ShaderDataType::Float3 }
		};

		m_TriangleArray.reset(Lumi::VertexArray::Create());

		std::shared_ptr<Lumi::VertexBuffer> vertexBufferT;
		vertexBufferT.reset(Lumi::VertexBuffer::Create(verticesT, sizeof(verticesT)));
		vertexBufferT->SetLayout(layoutT);
		m_TriangleArray->AddVertexBuffer(vertexBufferT);

		std::shared_ptr<Lumi::IndexBuffer> indexBufferT;
		indexBufferT.reset(Lumi::IndexBuffer::Create(indicesT, (unsigned int)std::size(indicesT)));
		m_TriangleArray->AddIndexBuffer(indexBufferT);

		vertexBufferT->Unbind();
		m_TriangleArray->Unbind();



		float verticesQ[] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		unsigned int indicesQ[] = {
			0, 1, 2,
			0, 2, 3
		};

		Lumi::BufferLayout layoutQ = {
			{ "aPosition", Lumi::ShaderDataType::Float3 },
			{ "aTexCoord", Lumi::ShaderDataType::Float2 }
		};

		m_QuadArray.reset(Lumi::VertexArray::Create());

		std::shared_ptr<Lumi::VertexBuffer> vertexBufferQ;
		vertexBufferQ.reset(Lumi::VertexBuffer::Create(verticesQ, sizeof(verticesQ)));
		vertexBufferQ->SetLayout(layoutQ);
		m_QuadArray->AddVertexBuffer(vertexBufferQ);

		std::shared_ptr<Lumi::IndexBuffer> indexBufferQ;
		indexBufferQ.reset(Lumi::IndexBuffer::Create(indicesQ, (unsigned int)std::size(indicesQ)));
		m_QuadArray->AddIndexBuffer(indexBufferQ);

		vertexBufferQ->Unbind();
		m_QuadArray->Unbind();

		auto quadShader = Lumi::ResourceManager::GetShader("QuadShader");
		std::dynamic_pointer_cast<Lumi::OpenGLShader>(quadShader)->Use();
		std::dynamic_pointer_cast<Lumi::OpenGLShader>(quadShader)->SetInt("uTexture", 0);

		// ------------------
		// ------------------
		////////////////////////////////////////////////////////////////////
	}

	void OnUpdate(Lumi::Timestep ts) override
	{
		//LUMI_CLIENT_INFO("DeltaTime: {0}s  {1}ms", ts.GetSeconds(), ts.GetMilliseconds());
		
		Lumi::RenderCommand::SetColor(0.117f, 0.117f, 0.117f, 1.0f);
		Lumi::RenderCommand::Clear();

		Lumi::Renderer::BeginScene(m_Camera);

		auto quadShader = Lumi::ResourceManager::GetShader("QuadShader");
		auto triangleShader = Lumi::ResourceManager::GetShader("TriangleShader");
		auto quadTexture = Lumi::ResourceManager::GetTexture2D("Barbara");

		std::dynamic_pointer_cast<Lumi::OpenGLShader>(quadShader)->Use();
		std::dynamic_pointer_cast<Lumi::OpenGLShader>(quadShader)->SetInt("uPng", false);
		std::dynamic_pointer_cast<Lumi::OpenGLShader>(quadShader)->SetVec3("uColor", m_QuadColor);

		Lumi::Renderer::Draw(quadShader, m_QuadArray);

		std::dynamic_pointer_cast<Lumi::OpenGLShader>(quadShader)->Use();
		std::dynamic_pointer_cast<Lumi::OpenGLShader>(quadShader)->SetInt("uPng", true);

		quadTexture->Bind();
		Lumi::Renderer::Draw(quadShader, m_QuadArray);
		//Lumi::Renderer::Draw(m_TriangleShader, m_TriangleArray);
		Lumi::Renderer::EndScene();
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Setting");
		ImGui::ColorEdit3("Quad Color", glm::value_ptr(m_QuadColor));
		ImGui::End();
	}

	void OnEvent(Lumi::Event& event) override
	{
		m_Camera.OnEvent(event);
	}
private:
	Lumi::Camera2D m_Camera;

	std::shared_ptr<Lumi::VertexArray> m_TriangleArray;
	std::shared_ptr<Lumi::VertexArray> m_QuadArray;

	glm::vec3 m_QuadColor = { 0.113f, 0.113f, 0.113f };
};

class Example : public Lumi::Application
{
public:
	Example();
	~Example();

private:
	
};

Example::Example()
{
	PushLayer(new ExampleLayer(m_Window->GetWidth(), m_Window->GetHeight()));
}

Example::~Example()
{
}

Lumi::Application* Lumi::CreateApplication()
{
	return new Example();
}