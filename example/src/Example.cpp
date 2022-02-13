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
		// A TESTING TRIANGLE
		// 
		m_Camera = Lumi::Camera2D(width, height, { 0.0f, 0.0f, 2.0f });

		std::string vertexShaderT = // vertex shader
			R"(
			#version 330 core
			
			layout(location = 0) in vec3 aPosition;
			layout(location = 1) in vec3 aColor;
			
			out vec3 Position;
			out vec3 Color;

			uniform mat4 uProjection;
			uniform mat4 uView;
			
			void main()
			{
				gl_Position = uProjection * uView * vec4(aPosition, 1.0);
				Position = aPosition;
				Color = aColor;
			}

		)";

		std::string fragmentShaderT = // fragment shader
			R"(
			#version 330 core
			
			in vec3 Position;
			in vec3 Color;
			
			out vec4 FragColor;
			
			void main()
			{
				FragColor = vec4(Color, 1.0);
			}

		)";

		m_TriangleShader.reset(new Lumi::Shader(vertexShaderT, fragmentShaderT));


		std::string vertexShaderQ = // vertex shader
			R"(
			#version 330 core
			
			layout(location = 0) in vec3 aPosition;

			uniform mat4 uProjection;
			uniform mat4 uView;
			
			void main()
			{
				gl_Position = uProjection * uView * vec4(aPosition, 1.0);
			}

		)";

		std::string fragmentShaderQ = // fragment shader
			R"(
			#version 330 core
			
			out vec4 FragColor;
			
			void main()
			{
				FragColor = vec4(0.3, 0.4, 0.7, 1.0);
			}

		)";

		m_QuadShader.reset(new Lumi::Shader(vertexShaderQ, fragmentShaderQ));



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
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		unsigned int indicesQ[] = {
			0, 1, 2,
			0, 2, 3
		};

		Lumi::BufferLayout layoutQ = {
			{ "aPosition", Lumi::ShaderDataType::Float3 }
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

		// ------------------
		// ------------------
		////////////////////////////////////////////////////////////////////
	}

	void OnUpdate(Lumi::Timestep ts) override
	{
		LUMI_CLIENT_INFO("DeltaTime: {0}s  {1}ms", ts.GetSeconds(), ts.GetMilliseconds());
		
		Lumi::RenderCommand::SetColor(0.117f, 0.117f, 0.117f, 1.0f);
		Lumi::RenderCommand::Clear();

		Lumi::Renderer::BeginScene(m_Camera);
		Lumi::Renderer::Draw(m_QuadShader, m_QuadArray);
		Lumi::Renderer::Draw(m_TriangleShader, m_TriangleArray);
		Lumi::Renderer::EndScene();
	}

	void OnImGuiRender() override
	{
		
	}

	void OnEvent(Lumi::Event& event) override
	{
		m_Camera.OnEvent(event);
	}
private:
	Lumi::Camera2D m_Camera;

	std::shared_ptr<Lumi::Shader> m_TriangleShader;
	std::shared_ptr<Lumi::VertexArray> m_TriangleArray;

	std::shared_ptr<Lumi::Shader> m_QuadShader;
	std::shared_ptr<Lumi::VertexArray> m_QuadArray;
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