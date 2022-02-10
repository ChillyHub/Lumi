#include "pch.h"
#include "Application.h"

#include "Lumi/Renderer/Renderer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Lumi
{
	
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;
	
	Application::Application()
	{
		LUMI_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;
		
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallBack(BIND_EVENT_FN(OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushLayer(m_ImGuiLayer);

		////////////////////////////////////////////////////////////////////
		// A TESTING TRIANGLE
		// ------------------
		std::string vertexShaderT = R"(
			#version 330 core
			
			layout(location = 0) in vec3 aPosition;
			layout(location = 1) in vec3 aColor;
			
			out vec3 Position;
			out vec3 Color;
			
			void main()
			{
				gl_Position = vec4(aPosition, 1.0);
				Position = aPosition;
				Color = aColor;
			}

		)";

		std::string fragmentShaderT = R"(
			#version 330 core
			
			in vec3 Position;
			in vec3 Color;
			
			out vec4 FragColor;
			
			void main()
			{
				FragColor = vec4(Color, 1.0);
			}

		)";

		m_TriangleShader.reset(new Shader(vertexShaderT, fragmentShaderT));


		std::string vertexShaderQ = R"(
			#version 330 core
			
			layout(location = 0) in vec3 aPosition;
			
			void main()
			{
				gl_Position = vec4(aPosition, 1.0);
			}

		)";

		std::string fragmentShaderQ = R"(
			#version 330 core
			
			out vec4 FragColor;
			
			void main()
			{
				FragColor = vec4(0.3, 0.4, 0.7, 1.0);
			}

		)";

		m_QuadShader.reset(new Shader(vertexShaderQ, fragmentShaderQ));



		float verticesT[] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
			 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
		};

		unsigned int indicesT[] = {
			0, 1, 2
		};

		BufferLayout layoutT = {
			{ "aPosition", ShaderDataType::Float3 },
			{ "aColor", ShaderDataType::Float3 }
		};

		m_TriangleArray.reset(VertexArray::Create());

		std::shared_ptr<VertexBuffer> vertexBufferT;
		vertexBufferT.reset(VertexBuffer::Create(verticesT, sizeof(verticesT)));
		vertexBufferT->SetLayout(layoutT);
		m_TriangleArray->AddVertexBuffer(vertexBufferT);
		
		std::shared_ptr<IndexBuffer> indexBufferT;
		indexBufferT.reset(IndexBuffer::Create(indicesT, (unsigned int)std::size(indicesT)));
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

		BufferLayout layoutQ = {
			{ "aPosition", ShaderDataType::Float3 }
		};

		m_QuadArray.reset(VertexArray::Create());

		std::shared_ptr<VertexBuffer> vertexBufferQ;
		vertexBufferQ.reset(VertexBuffer::Create(verticesQ, sizeof(verticesQ)));
		vertexBufferQ->SetLayout(layoutQ);
		m_QuadArray->AddVertexBuffer(vertexBufferQ);

		std::shared_ptr<IndexBuffer> indexBufferQ;
		indexBufferQ.reset(IndexBuffer::Create(indicesQ, (unsigned int)std::size(indicesQ)));
		m_QuadArray->AddIndexBuffer(indexBufferQ);

		vertexBufferQ->Unbind();
		m_QuadArray->Unbind();
		
		// ------------------
		// ------------------
		////////////////////////////////////////////////////////////////////
	}

	Application::~Application()
	{

	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispathcher(e);
		dispathcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(CloseWindow));

		// LUMI_CORE_INFO("{0}", e);

		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
		{
			(*it)->OnEvent(e);
			if (e.m_Handled)
				break;
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach(); 
	}
	
	void Application::Run()
	{
		WindowResizeEvent e(1920, 1080);
		if (e.IsInCategory(EVENT_CATEGORY_APPLICATION))
		{
			LUMI_CLIENT_TRACE(e);
		}
		if (e.IsInCategory(EVENT_CATEGORY_INPUT))
		{
			LUMI_CLIENT_ERROR(e);
		}

		while (m_Running)
		{
			RenderCommand::SetColor(0.117f, 0.117f, 0.117f, 1.0f);
			RenderCommand::Clear();

			Renderer::BeginScene();

			m_QuadShader->Use();
			Renderer::Submit(m_QuadArray);

			m_TriangleShader->Use();
			Renderer::Submit(m_TriangleArray);

			Renderer::EndScene();


			m_ImGuiLayer->Begin();
			for (auto layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	bool Application::CloseWindow(WindowCloseEvent& e)
	{
		return m_Running = false;
	}
}