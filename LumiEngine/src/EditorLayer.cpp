#include "EditorLayer.h"

#include "example/Example.hpp"

#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Lumi
{
	EditorLayer::EditorLayer()
		: Layer("Editor Layer"), m_Camera2D(Camera2D()), m_Camera3D(Camera3D())
	{
		LM_PROFILE_FUNCTION();

        //m_Framebuffer = Framebuffer::Create(FramebufferSpecification());

        m_Texture = ResourceManager::LoadTexture2D("assets/textures/barbara2.png", "Barbara");
	}

	EditorLayer::~EditorLayer()
	{
		LM_PROFILE_FUNCTION();
	}
	
	void EditorLayer::OnAttach()
	{
		LM_PROFILE_FUNCTION();
	}

	void EditorLayer::OnDetach()
	{
		LM_PROFILE_FUNCTION();
	}

	void EditorLayer::OnUpdate(Timestep ts)
	{
		LM_PROFILE_FUNCTION();
	}

	void EditorLayer::OnImGuiRender()
	{
		LM_PROFILE_FUNCTION();

        //_______________________________________________________________________________________________
        // SHOW DOCKING SPACE ///////////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////////////////////////////////
		static bool dockspaceOpen = true;
		static bool opt_fullscreen_persistant = true;
        static bool opt_fullscreen = true;
        static bool opt_padding = false;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
        // because it would be confusing to have two docking targets within each others.
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen)
        {
            const ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->WorkPos);
            ImGui::SetNextWindowSize(viewport->WorkSize);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | 
                ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }
        else
        {
            dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
        }

        // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
        // and handle the pass-thru hole, so we ask Begin() to not render a background.
        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
        // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
        // all active windows docked into it will lose their parent and become undocked.
        // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
        // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
        if (!opt_padding)
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
        if (!opt_padding)
            ImGui::PopStyleVar();

        if (opt_fullscreen)
            ImGui::PopStyleVar(2);

        // Submit the DockSpace
        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }

        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                // Disabling fullscreen would allow the window to be moved to the front of other windows,
                // which we can't undo at the moment without finer window depth/z control.
                // ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen);
                //ImGui::MenuItem("Padding", NULL, &opt_padding);
                ImGui::Separator();
                
                //if (ImGui::MenuItem("Flag: NoSplit", "", 
                //    (dockspace_flags & ImGuiDockNodeFlags_NoSplit) != 0)) 
                //{ dockspace_flags ^= ImGuiDockNodeFlags_NoSplit; }
                //if (ImGui::MenuItem("Flag: NoResize", "", 
                //    (dockspace_flags & ImGuiDockNodeFlags_NoResize) != 0)) 
                //{ dockspace_flags ^= ImGuiDockNodeFlags_NoResize; }
                //if (ImGui::MenuItem("Flag: NoDockingInCentralNode", "", 
                //    (dockspace_flags & ImGuiDockNodeFlags_NoDockingInCentralNode) != 0)) 
                //{ dockspace_flags ^= ImGuiDockNodeFlags_NoDockingInCentralNode; }
                //if (ImGui::MenuItem("Flag: AutoHideTabBar", "", 
                //    (dockspace_flags & ImGuiDockNodeFlags_AutoHideTabBar) != 0)) 
                //{ dockspace_flags ^= ImGuiDockNodeFlags_AutoHideTabBar; }
                //if (ImGui::MenuItem("Flag: PassthruCentralNode", "", 
                //    (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) != 0, opt_fullscreen)) 
                //{ dockspace_flags ^= ImGuiDockNodeFlags_PassthruCentralNode; }
                ImGui::Separator();

                //if (ImGui::MenuItem("Close", NULL, false))
                //    dockspaceOpen = false;
                ImGui::EndMenu();
            }

            ImGui::EndMenuBar();
        }

        ImGui::End();

        //_______________________________________________________________________________________________
        // SHOW DOCKING SPACE END ///////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////////////////////////////////

        ImGui::Begin("View");
        ImGui::Image((void*)m_Texture->GetTexID(), ImVec2{1024, 1024}, {0, 1}, {1, 0});
        ImGui::End();

        ImGui::ShowDemoWindow();
	}

	void EditorLayer::OnEvent(Event& event)
	{
		LM_PROFILE_FUNCTION();
	}
}