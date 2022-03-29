#include <Lumi.h>
#include <Lumi/Core/EntryPoint.h>

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

		Lumi::ResourceManager::LoadTexture2D("assets/textures/barbara2.png", "Barbara", true);
		Lumi::ResourceManager::LoadTexture2D("assets/textures/bronya2.png", "Bronya", true);
		Lumi::ResourceManager::LoadTexture2D("assets/textures/ei.png", "Ei", true);
		Lumi::ResourceManager::LoadTexture2D("assets/textures/ganyu_keqing.png", "Ganyu", true);
		Lumi::ResourceManager::LoadTexture2D("assets/textures/keqing.png", "Keqing", true);

		Lumi::Renderer2D::Init(true);

		auto frameSpec = Lumi::FramebufferSpecification();
		frameSpec.Width = width;
		frameSpec.Height = height;
		auto colorTexSpec = Lumi::TexSpecCreator::Create();
		auto depthTexSpec = Lumi::TexSpecCreator::Create(Lumi::TextureType::DepthMap);

		m_Framebuffer = Lumi::Framebuffer::Create(frameSpec);
		//m_Framebuffer->AddTexBuffer(depthTexSpec);
		m_ColorTex = m_Framebuffer->AddTexBuffer(colorTexSpec);

		// ------------------
		// ------------------
		////////////////////////////////////////////////////////////////////
	}

	void OnUpdate(Lumi::Timestep ts) override
	{
		//LUMI_CLIENT_INFO("DeltaTime: {0}s  {1}ms", ts.GetSeconds(), ts.GetMilliseconds());
		LM_PROFILE_FUNCTION();
		m_Framebuffer->Bind();
	{
		LM_PROFILE_SCOPE("Render_Reset");
		Lumi::RenderCommand::SetColor(0.117f, 0.117f, 0.117f, 1.0f);
		Lumi::RenderCommand::Clear();
		Lumi::Renderer2D::ResetStats();
	}	
		auto quadTexture1 = Lumi::ResourceManager::GetTexture2D("Barbara");
		auto quadTexture2 = Lumi::ResourceManager::GetTexture2D("Bronya");
		auto quadTexture3 = Lumi::ResourceManager::GetTexture2D("Ei");
		auto quadTexture4 = Lumi::ResourceManager::GetTexture2D("Ganyu");
		auto quadTexture5 = Lumi::ResourceManager::GetTexture2D("Keqing");
		std::vector textures { quadTexture1, quadTexture2, quadTexture3, quadTexture4, quadTexture5 };
	{
		LM_PROFILE_SCOPE("Draw_Quad");
		// Lumi::Renderer2D::BeginScene(m_Camera);
		// Lumi::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.02f }, { 1.0f, 1.0f }, m_QuadColor, 0.0f);
		// Lumi::Renderer2D::DrawQuad(quadTexture1, { 0.0f, 0.0f, -0.01f }, { 1.0f, 1.0f },
		// 	{ 1.0f, 1.0f, 1.0f }, 0.0f);
		// Lumi::Renderer2D::EndScene();
		Lumi::Renderer2D::BeginScene(m_Camera);
		for (float x = 0.0f, i = 0.0f; x < 50.0f; x += 1.2f)
		{
			for (float y = 0.0f; y < 50.0f; y += 1.2f, i++)
			{
				auto texture = textures[(int)i % textures.size()];
				Lumi::Renderer2D::DrawQuad({ x, y, -0.01f }, { 1.0f, 1.0f }, m_QuadColor, 0.0f);
				Lumi::Renderer2D::DrawQuad(texture, { x, y, 0.0f }, { 1.0f, 1.0f },
					{ 1.0f, 1.0f, 1.0f }, 0.0f);
			}
		}
		Lumi::Renderer2D::EndScene();
	}
		m_Framebuffer->UnBind();

		//Lumi::RenderCommand::SetColor(0.117f, 0.117f, 0.117f, 1.0f);
		//Lumi::RenderCommand::Clear();
		//Lumi::Renderer2D::BeginFrame();
		//auto texture = m_Framebuffer->GetTexture2D(m_ColorTex);
		//Lumi::Renderer2D::DrawFrame(texture);
		//Lumi::Renderer2D::EndFrame();
	}

	void OnImGuiRender() override
	{
		LM_PROFILE_FUNCTION();

		ImGui::Begin("Stats");
		auto stat = Lumi::Renderer2D::GetStats();
		ImGui::Text("Renderer2D Stats: ");
		ImGui::Text("Draw Calls: %d", stat.DrawCall);
		ImGui::Text("Quad Count: %d", stat.QuadCount);
		ImGui::Text("Vertices Count: %d", stat.GetVerteicesCount());
		ImGui::Text("Indices Count: %d", stat.GetIndicesCount());
		ImGui::End();
		
		ImGui::Begin("Setting");
		ImGui::ColorEdit3("Quad Color", glm::value_ptr(m_QuadColor));
		ImGui::End();
	}

	void OnEvent(Lumi::Event& event) override
	{
		LM_PROFILE_FUNCTION();

		m_Camera.OnEvent(event);
		//m_Framebuffer->OnEvent(event);
	}

	std::shared_ptr<Lumi::Framebuffer> GetFramebuffer()
	{
		return m_Framebuffer;
	}
private:
	Lumi::Camera2D m_Camera;

	glm::vec3 m_QuadColor = { 0.113f, 0.113f, 0.113f };

	std::shared_ptr<Lumi::Framebuffer> m_Framebuffer;
	unsigned int  m_ColorTex;
};