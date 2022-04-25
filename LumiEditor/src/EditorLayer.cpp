#include "EditorLayer.h"

#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Example/Example1.hpp"
#include "Example/Example2.hpp"

namespace Lumi
{
	EditorLayer::EditorLayer(unsigned int width, unsigned int height)
		: Layer("Editor Layer")
	{
		LM_PROFILE_FUNCTION();

        //m_Framebuffer = Framebuffer::Create(FramebufferSpecification());

        //ImVec2 viewportSize = ImGui::GetContentRegionAvail();
        m_EditorScene = std::make_shared<EditorScene>();
        //m_ViewportSize = { 1920, 1080 };

        //m_Camera2D = Lumi::Camera2D((int)m_ViewportSize.x, (int)m_ViewportSize.y, { 0.0f, 0.0f, 2.0f });

        //Lumi::ResourceManager::LoadTexture2D("assets/textures/barbara2.png", "Barbara", true);
        //Lumi::ResourceManager::LoadTexture2D("assets/textures/bronya2.png", "Bronya", true);
        //Lumi::ResourceManager::LoadTexture2D("assets/textures/ei.png", "Ei", true);
        //Lumi::ResourceManager::LoadTexture2D("assets/textures/ganyu_keqing.png", "Ganyu", true);
        //Lumi::ResourceManager::LoadTexture2D("assets/textures/keqing.png", "Keqing", true);

        Lumi::Renderer2D::Init(true);

        auto frameSpec = Lumi::FramebufferSpecification();
        frameSpec.Width = width;
        frameSpec.Height = height;
        auto colorTexSpec = Lumi::TexSpecCreator::Create();
        auto depthTexSpec = Lumi::TexSpecCreator::Create(Lumi::TextureType::DepthMap);

        m_Framebuffer = Lumi::Framebuffer::Create(frameSpec);
        //m_Framebuffer->AddTexBuffer(depthTexSpec);
        m_ColorTex = m_Framebuffer->AddTexBuffer(colorTexSpec);

        m_Scene = std::make_shared<Scene>();
        //auto& quads = m_Scene->CreateEntity("Quads");
        //quads.AddComponent<Script>().Bind<Example1>();
        auto& quads = m_Scene->CreateEntity("Quad");
        quads.AddComponent<Script>().Bind<Example2>();

        m_SceneUI->SetContext(m_Scene);
        m_SceneUI->SetEditor(m_EditorScene);
        m_PropertiesUI->SetScene(m_SceneUI);

        //auto quadTexture1 = Lumi::ResourceManager::GetTexture2D("Barbara");
        //auto quadTexture2 = Lumi::ResourceManager::GetTexture2D("Bronya");
        //auto quadTexture3 = Lumi::ResourceManager::GetTexture2D("Ei");
        //auto quadTexture4 = Lumi::ResourceManager::GetTexture2D("Ganyu");
        //auto quadTexture5 = Lumi::ResourceManager::GetTexture2D("Keqing");
        //std::vector textures{ quadTexture1, quadTexture2, quadTexture3, quadTexture4, quadTexture5 };
        //
        //for (float x = 0.0f, i = 0.0f; x < 50.0f; x += 1.2f)
        //{
        //    for (float y = 0.0f; y < 50.0f; y += 1.2f, i++)
        //    {
        //        auto quad1 = m_Scene->CreateEntity("Entity" + std::to_string(2 * i));
        //        auto texture = textures[(int)i % textures.size()];
        //        auto& transform1 = quad1.GetComponent<Transform>();
        //        transform1.Position = { x, y, 0.0f };
        //        transform1.Scale = { 1.0f, 1.0f, 1.0f };
        //        transform1.Rotation = { 1.0f, 0.0f, 0.0f, 0.0f };
        //        quad1.AddComponent<Material2D>(texture, glm::vec4(1.0f));
        //        auto quad2 = m_Scene->CreateEntity("Entity" + std::to_string(2 * i + 1));
        //        auto& transform2 = quad2.GetComponent<Transform>();
        //        transform2.Position = { x, y, -0.01f };
        //        transform2.Scale = { 1.0f, 1.0f, 1.0f };
        //        transform2.Rotation = { 1.0f, 0.0f, 0.0f, 0.0f };
        //        quad2.AddComponent<Material2D>(m_QuadColor);
        //        
        //    }
        //}
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

        m_EditorScene->EditorUpdate(ts);

        m_Framebuffer->Bind();
        {
            LM_PROFILE_SCOPE("Render_Reset");
            Lumi::RenderCommand::SetColor(0.117f, 0.117f, 0.117f, 1.0f);
            Lumi::RenderCommand::Clear();
            Lumi::Renderer2D::ResetStats();
        }
        //auto quadTexture1 = Lumi::ResourceManager::GetTexture2D("Barbara");
        //auto quadTexture2 = Lumi::ResourceManager::GetTexture2D("Bronya");
        //auto quadTexture3 = Lumi::ResourceManager::GetTexture2D("Ei");
        //auto quadTexture4 = Lumi::ResourceManager::GetTexture2D("Ganyu");
        //auto quadTexture5 = Lumi::ResourceManager::GetTexture2D("Keqing");
        //std::vector textures{ quadTexture1, quadTexture2, quadTexture3, quadTexture4, quadTexture5 };
        {
            LM_PROFILE_SCOPE("Draw_Quad");
            // Lumi::Renderer2D::BeginScene(m_Camera);
            // Lumi::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.02f }, { 1.0f, 1.0f }, m_QuadColor, 0.0f);
            // Lumi::Renderer2D::DrawQuad(quadTexture1, { 0.0f, 0.0f, -0.01f }, { 1.0f, 1.0f },
            // 	{ 1.0f, 1.0f, 1.0f }, 0.0f);
            // Lumi::Renderer2D::EndScene();
            auto& camera = m_CameraType ?
                m_EditorScene->GetCamera3D() : m_EditorScene->GetCamera2D();
            if (m_CameraType)
            {
                m_EditorScene->GetCamera3D().Activated = true;
                m_EditorScene->GetCamera2D().Activated = false;
                m_EditorScene->GetCamera3D().entity
                    ->GetComponent<Script>().Activated = true;
                m_EditorScene->GetCamera2D().entity
                    ->GetComponent<Script>().Activated = false;
            }
            else
            {
                m_EditorScene->GetCamera3D().Activated = false;
                m_EditorScene->GetCamera2D().Activated = true;
                m_EditorScene->GetCamera3D().entity
                    ->GetComponent<Script>().Activated = false;
                m_EditorScene->GetCamera2D().entity
                    ->GetComponent<Script>().Activated = true;
            }
            Lumi::Renderer2D::BeginScene(camera);
            //for (float x = 0.0f, i = 0.0f; x < 50.0f; x += 1.2f)
            //{
            //    for (float y = 0.0f; y < 50.0f; y += 1.2f, i++)
            //    {
            //        auto texture = textures[(int)i % textures.size()];
            //        Lumi::Renderer2D::DrawQuad({ x, y, -0.01f }, { 1.0f, 1.0f }, m_QuadColor, 0.0f);
            //        Lumi::Renderer2D::DrawQuad(texture, { x, y, 0.0f }, { 1.0f, 1.0f },
            //            { 1.0f, 1.0f, 1.0f }, 0.0f);
            //    }
            //}
            m_Scene->OnUpdate2D(ts, m_QuadColor);
            Lumi::Renderer2D::EndScene();
        }
        m_Framebuffer->UnBind();
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
        ImGuiStyle& style = ImGui::GetStyle();
        float minWinSizeX = style.WindowMinSize.x;
        style.WindowMinSize.x = 420.0f;
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }
        style.WindowMinSize.x = minWinSizeX;

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

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
        ImGui::Begin("View");
        m_ViewportFocus = ImGui::IsWindowFocused();
        m_ViewportHover = ImGui::IsWindowHovered();
        ImVec2 size = ImGui::GetContentRegionAvail();
        if (m_ViewportSize != *((glm::vec2*)&size))
        {
            m_ViewportSize = { size.x, size.y };
            m_Framebuffer->Resize((unsigned int)m_ViewportSize.x, (unsigned int)m_ViewportSize.y);
            auto& camera2D = m_EditorScene->GetCamera2D();
            camera2D.Aspect = m_ViewportSize.x / m_ViewportSize.y;
            camera2D.ScreenWidth = m_ViewportSize.x;
            camera2D.ScreenHeight = m_ViewportSize.y;
            auto& camera3D = m_EditorScene->GetCamera3D();
            camera3D.Aspect = m_ViewportSize.x / m_ViewportSize.y;
            camera3D.ScreenWidth = m_ViewportSize.x;
            camera3D.ScreenHeight = m_ViewportSize.y;
            //m_Camera2D.Resize(m_ViewportSize.x, m_ViewportSize.y);
        }
        auto& script = m_EditorScene->GetCameraScript2D();
        script.IsHovered = m_ViewportHover;
        ImGui::Image((void*)(unsigned long long)m_Framebuffer->GetTexID(0), 
            ImVec2{m_ViewportSize.x, m_ViewportSize.y}, {0, 1}, {1, 0});
        ImGui::End();
        ImGui::PopStyleVar();

        ImGui::Begin("Select Editor Camera");
        const char* cameraTypes[] = { "Camera2D", "Camera3D" };
        const char* currentType = cameraTypes[(int)m_CameraType];
        if (ImGui::BeginCombo("Projection", currentType))
        {
            for (int i = 0; i < 2; i++)
            {
                bool isSelected = currentType == cameraTypes[i];
                if (ImGui::Selectable(cameraTypes[i], isSelected))
                {
                    currentType = cameraTypes[i];
                    m_CameraType = (unsigned int)i;
                }

                if (isSelected)
                {
                    ImGui::SetItemDefaultFocus();
                }
            }

            ImGui::EndCombo();
        }
        ImGui::End();

        m_SceneUI->OnImGuiRender();
        m_PropertiesUI->OnImGuiRender();

        //ImGui::Begin("Setting");
        ////ImGui::ColorEdit3("Quad Color", glm::value_ptr(m_QuadColor));
        //ImGui::Separator();
        //
        //auto entities = m_Scene->GetRegistry().view<Script>();
        //for (auto entity : entities)
        //{
        //    auto [script] = entities.get(entity);
        //    //script.QuadColor = glm::vec4(m_QuadColor, 1.0f);
        //    //if (m_QuadColor != m_LastColor && material.Texture2D == nullptr)
        //    //{
        //    //    material.QuadColor = glm::vec4(m_QuadColor, 1.0f);
        //    //}
        //    ImGui::ColorEdit3("Quads Color", 
        //        glm::value_ptr(script.GetInstance<Example1>().QuadColor));
        //    ImGui::Separator();
        //}
        //m_LastColor = m_QuadColor;
        //ImGui::End();
	}

	void EditorLayer::OnEvent(Event& event)
	{
		LM_PROFILE_FUNCTION();

        //if (m_ViewportHover)
        //{
        //    m_Camera2D.OnEvent(event);
        //}
        //else
        //{
        //    m_Camera2D.OnEvent2(event);
        //}
        //m_Framebuffer->OnEvent(event);
	}
}