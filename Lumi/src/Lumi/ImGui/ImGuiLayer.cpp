#include "pch.h"
#include "ImGuiLayer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include "Lumi/Core/Application.h"
#include "UI/Function/Gizmos.h"

#define GLSL_VERSION "#version 410"

namespace Lumi
{
	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{
		LM_PROFILE_FUNCTION();
	}

	ImGuiLayer::~ImGuiLayer()
	{
		LM_PROFILE_FUNCTION();
	}

	void ImGuiLayer::OnAttach()
	{
		LM_PROFILE_FUNCTION();
		
		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

		// Setup Dear ImGui style
		SetDarkThemeColors();

		// Load Fonts
		float fontsize = 20.0f;
		io.Fonts->AddFontFromFileTTF("assets/fonts/msyh.ttc",
			fontsize, NULL, io.Fonts->GetGlyphRangesChineseSimplifiedCommon());
		io.Fonts->AddFontFromFileTTF("assets/fonts/msyhbd.ttc",
			fontsize, NULL, io.Fonts->GetGlyphRangesChineseSimplifiedCommon());

		// Setup Platform/Renderer backends
		Application& app = Application::Get();
		ImGui_ImplGlfw_InitForOpenGL(static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow()), true);
		LUMI_CORE_ASSERT(app.GetWindow().GetNativeWindow(), "Wrong");
		ImGui_ImplOpenGL3_Init(GLSL_VERSION);
	}

	void ImGuiLayer::OnDetach()
	{
		LM_PROFILE_FUNCTION();
		
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::OnImGuiRender()
	{
		LM_PROFILE_FUNCTION();
		
		// static bool show = true;
		// ImGui::ShowDemoWindow(&show);
	}

	void ImGuiLayer::OnEvent(Event& event)
	{
		LM_PROFILE_FUNCTION();

		ImGuiIO& io = ImGui::GetIO();
		event.m_Handled |= event.IsInCategory(EventCategory::EVENT_CATEGORY_MOUSE) && io.WantCaptureMouse;
		event.m_Handled |= event.IsInCategory(EventCategory::EVENT_CATEGORY_KEYBOARD) && io.WantCaptureKeyboard;
	}

	void ImGuiLayer::Begin()
	{
		LM_PROFILE_FUNCTION(); 
		
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());

		float time = (float)glfwGetTime();
		io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
		m_Time = time;
		
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		Gizmos::BeginFrame();
	}

	void ImGuiLayer::End()
	{
		LM_PROFILE_FUNCTION(); 
		
		ImGuiIO& io = ImGui::GetIO();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}

	void ImGuiLayer::SetDarkThemeColors()
	{
		LM_PROFILE_FUNCTION(); 
		
		ImGuiStyle& style = ImGui::GetStyle();
		style.WindowRounding = 13.0f;
		style.ChildRounding = 13.0f;
		style.FrameRounding = 13.0f;
		style.GrabRounding = 13.0f;
		style.PopupRounding = 13.0f;
		style.ScrollbarRounding = 13.0f;
		style.TabRounding = 5.0f;
		
		auto& colors = style.Colors;
		colors[ImGuiCol_WindowBg] = ImVec4{ 0.1f, 0.105f, 0.11f, 1.0f };

		// Headers
		colors[ImGuiCol_Header] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_HeaderActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		// Buttons
		colors[ImGuiCol_Button] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_ButtonActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		// Frame BG
		colors[ImGuiCol_FrameBg] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		// Tabs
		colors[ImGuiCol_Tab] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TabHovered] = ImVec4{ 0.38f, 0.3805f, 0.381f, 1.0f };
		colors[ImGuiCol_TabActive] = ImVec4{ 0.28f, 0.2805f, 0.281f, 1.0f };
		colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };

		// Title
		colors[ImGuiCol_TitleBg] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
	}

}