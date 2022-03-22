#include <Lumi.h>

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui.h>

class ExampleLayer : public Lumi::Layer
{
public:
	ExampleLayer(int width, int height) : Layer("Example")
	{
		////////////////////////////////////////////////////////////////////
		// A TESTING QUAD
		// 
		m_Camera = Lumi::Camera2D(width, height, { 0.0f, 0.0f, 2.0f });

		Lumi::ResourceManager::LoadShader
		("shaders/shaderQ.vert", "shaders/shaderQ.frag", nullptr, "Shader2D");

		Lumi::ResourceManager::LoadTexture2D("assets/textures/barbara2.png", "Barbara", true);

		Lumi::Renderer2D::Init();

		// ------------------
		// ------------------
		////////////////////////////////////////////////////////////////////
	}

	void OnUpdate(Lumi::Timestep ts) override
	{
		//LUMI_CLIENT_INFO("DeltaTime: {0}s  {1}ms", ts.GetSeconds(), ts.GetMilliseconds());
		LM_PROFILE_FUNCTION();
	{
		LM_PROFILE_SCOPE("Render_Reset");
		Lumi::RenderCommand::SetColor(0.117f, 0.117f, 0.117f, 1.0f);
		Lumi::RenderCommand::Clear();
	}
	{
		LM_PROFILE_SCOPE("Camera_change");
		Lumi::Renderer2D::BeginScene(m_Camera);
	}
		auto quadTexture = Lumi::ResourceManager::GetTexture2D("Barbara");
	{
		LM_PROFILE_SCOPE("Draw_Quad");
		Lumi::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.01f }, { 1.0f, 1.0f }, m_QuadColor);
		Lumi::Renderer2D::DrawQuad(quadTexture);
	}
		Lumi::Renderer2D::EndScene();
	}

	void OnImGuiRender() override
	{
		LM_PROFILE_FUNCTION();
		
		ImGui::Begin("Setting");
		ImGui::ColorEdit3("Quad Color", glm::value_ptr(m_QuadColor));
		ImGui::End();
	}

	void OnEvent(Lumi::Event& event) override
	{
		LM_PROFILE_FUNCTION();

		m_Camera.OnEvent(event);
	}
private:
	Lumi::Camera2D m_Camera;

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