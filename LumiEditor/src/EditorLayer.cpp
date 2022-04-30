#include "EditorLayer.h"

#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "UI/Function/Gizmos.h"

#include "Example/Example1.hpp"
#include "Example/Example2.hpp"

namespace Lumi
{
	EditorLayer::EditorLayer(unsigned int width, unsigned int height)
		: Layer("Editor Layer")
	{
		LM_PROFILE_FUNCTION();

        //ImVec2 viewportSize = ImGui::GetContentRegionAvail();
        m_EditorScene = std::make_shared<EditorScene>();
        //m_ViewportSize = { 1920, 1080 };

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
        //auto& quads = m_Scene->CreateEntity("Quad");
        //quads.AddComponent<Script>().Bind<Example2>();

        m_SceneUI->SetContext(m_Scene);
        m_SceneUI->SetEditor(m_EditorScene);
        m_PropertiesUI->SetScene(m_SceneUI);
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

        if (!m_CurrentFilepath.empty())
        {
            Application::Get().GetWindow().SetTitle(
                std::format("Lumi [{0}]", m_CurrentFilepath));
        }
        else
        {
            Application::Get().GetWindow().SetTitle("Lumi");
        }

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
                if (ImGui::MenuItem("New", "Ctrl N"))
                {
                    NewScene();
                }
                if (ImGui::MenuItem("Open...", "Ctrl O"))
                {
                    OpenScene();
                }
                ImGui::Separator();

                if (ImGui::MenuItem("Save", "Ctrl S"))
                {
                    SaveScene();
                }
                if (ImGui::MenuItem("Save As...", "Shift Ctrl S"))
                {
                    SaveSceneAs();
                }
                ImGui::Separator();

                if (ImGui::MenuItem("Quit", "Ctrl Q"))
                {
                    Application::Get().Close();
                }

                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Edit"))
            {
                if (ImGui::MenuItem("Preferences"))
                {

                }
                
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Window"))
            {
                if (ImGui::MenuItem("New Window"))
                {

                }
                
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Help"))
            {
                if (ImGui::MenuItem("About Lumi"))
                {

                }
                
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
        auto& script2D = m_EditorScene->GetCameraScript2D();
        script2D.IsHovered = m_ViewportHover;
        script2D.IsFocused = m_ViewportFocus;
        auto& script3D = m_EditorScene->GetCameraScript3D();
        script3D.IsHovered = m_ViewportHover;
        script3D.IsFocused = m_ViewportFocus;
        ImGui::Image((void*)(unsigned long long)m_Framebuffer->GetTexID(0), 
            ImVec2{m_ViewportSize.x, m_ViewportSize.y}, {0, 1}, {1, 0});

        // Gizmos
        auto selectEntity = m_SceneUI->GetSelectedEntity();
        Camera& camera2D = m_EditorScene->GetCamera2D();
        Camera& camera3D = m_EditorScene->GetCamera3D();
        Camera& camera = m_CameraType ? camera3D : camera2D;
        if (selectEntity && m_GizmosType > 0)
        {
            if (camera.Projection == ProjectionType::Orthographic)
            {
                Gizmos::SetOrthographic(true);
            }
            else
            {
                Gizmos::SetOrthographic(false);
            }

            bool snap = Input::IsKeyPressed(Key::LeftCtrl);
            float snapValue = 1.0f;
            float snapAngle = 5.0f;
            float snapValues[3] = { snapValue, snapValue, snapValue };
            float snapAngles[3] = { snapAngle, snapAngle, snapAngle };

            Gizmos::SetDrawlist();
            float width = (float)ImGui::GetWindowWidth();
            float height = (float)ImGui::GetWindowHeight();
            Gizmos::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y,
                width, height);

            const auto& projectMat = camera.GetProjectionMatrix();
            const auto& viewMat = camera.GetViewMatrix();
            auto transformMat = selectEntity->transform.GetModelMatrix();
            Gizmos::Manipulate(glm::value_ptr(viewMat), glm::value_ptr(projectMat),
                (Gizmos::OPERATION)m_GizmosType, (Gizmos::MODE)m_GizmosSpace,
                glm::value_ptr(transformMat), nullptr, 
                snap ? snapValues : nullptr);

            if (Gizmos::IsUsing())
            {
                auto& position = selectEntity->transform.Position;
                auto& rotation = selectEntity->transform.Rotation;
                auto& scale = selectEntity->transform.Scale;
                auto eularAngle = glm::degrees(glm::eulerAngles(rotation));
                
                Gizmos::DecomposeMatrixToComponents(glm::value_ptr(transformMat),
                    glm::value_ptr(position), 
                    glm::value_ptr(eularAngle), 
                    glm::value_ptr(scale));
                rotation = glm::quat(glm::radians(eularAngle));
            } 
        }

        ImGui::End();
        ImGui::PopStyleVar();

        ImGui::Begin("Gizmos");
        ImGui::Columns(2);
        ImGui::SetColumnWidth(0, 100.0f);

        const char* gizmosSpaces[] = { "Local", "World" };
        const char* gizmosSpace = gizmosSpaces[m_GizmosSpace];
        ImGui::Text("Space");
        ImGui::NextColumn();
        if (ImGui::BeginCombo("##Space", gizmosSpace))
        {
            for (int i = 0; i < 2; i++)
            {
                bool isSelected = gizmosSpace == gizmosSpaces[i];
                if (ImGui::Selectable(gizmosSpaces[i], isSelected))
                {
                    gizmosSpace = gizmosSpaces[i];
                    m_GizmosSpace = i;
                }
                if (isSelected)
                {
                    ImGui::SetItemDefaultFocus();
                }
            }
            ImGui::EndCombo();
        }
        ImGui::NextColumn();

        ImGui::Text("Move");
        ImGui::NextColumn();
        ImGui::Checkbox("##Move", &m_Move);
        ImGui::NextColumn();
        ImGui::Text("Rotate");
        ImGui::NextColumn();
        ImGui::Checkbox("##Rotate", &m_Rote);
        ImGui::NextColumn();
        ImGui::Text("Scale");
        ImGui::NextColumn();
        ImGui::Checkbox("##Scale", &m_Scal);
        ImGui::Columns(1);

        m_GizmosType = 0;
        if (m_Move) m_GizmosType |= Gizmos::OPERATION::TRANSLATE;
        if (m_Rote) m_GizmosType |= Gizmos::OPERATION::ROTATE;
        if (m_Scal) m_GizmosType |= Gizmos::OPERATION::SCALE;
        ImGui::End();

        ImGui::Begin("Select Editor Camera");
        ImGui::Columns(2);
        ImGui::SetColumnWidth(0, 100.0f);
        ImGui::Text("Camera");
        ImGui::NextColumn();
        const char* cameraTypes[] = { "Camera2D", "Camera3D" };
        const char* currentType = cameraTypes[(int)m_CameraType];
        if (ImGui::BeginCombo("##Camera Type", currentType))
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
        ImGui::NextColumn();

        ImGui::Text("Projection");
        ImGui::NextColumn();
        const char* projectTypes[] = { "Perspective", "Orthographic" };
        const char* projectType = projectTypes[(int)camera.Projection];
        if (ImGui::BeginCombo("##Projection", projectType))
        {
            for (int i = 0; i < 2; i++)
            {
                bool isSelected = projectType == projectTypes[i];
                if (ImGui::Selectable(projectTypes[i], isSelected))
                {
                    projectType = projectTypes[i];
                    camera.Projection = (ProjectionType)i;
                }
                if (isSelected)
                {
                    ImGui::SetItemDefaultFocus();
                }
            }

            ImGui::EndCombo();
        }
        ImGui::Columns(1);
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

        m_EditorScene->OnEvent(event);
        m_Scene->OnEvent(event);

        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<KeyPressedEvent>(
            BIND_EVENT_FN(EditorLayer::OnKeyPressed));
        dispatcher.Dispatch<MouseButtonPressedEvent>(
            BIND_EVENT_FN(EditorLayer::OnMousePressed));
	}

    void EditorLayer::NewScene()
    {
        m_Scene->ClearEntities();
        m_Scene = std::make_shared<Scene>();
        m_SceneUI->SetContext(m_Scene);
        m_PropertiesUI->SetScene(m_SceneUI);
        m_CurrentFilepath = std::string();
    }

    void EditorLayer::OpenScene()
    {
        std::string filepath = FileDialogs::OpenFile(
            "Lumi Scene (*.lumiscene)\0*.lumiscene\0");
        if (!filepath.empty())
        {
            OpenScene(filepath);
            m_CurrentFilepath = filepath;
        }
    }

    void EditorLayer::OpenScene(const std::filesystem::path& path)
    {
        if (path.extension().string() != ".lumiscene")
        {
            LUMI_CLIENT_WARN("Can't open file: {0} :: Not a scene file",
                path.filename().string());
            return;
        }

        std::shared_ptr<Scene> newScene = std::make_shared<Scene>();
        Serializer ser;
        if (ser.Deserialize(newScene.get(), path.string()))
        {
            m_Scene->ClearEntities();
            m_Scene = newScene;
            m_SceneUI->SetContext(m_Scene);
            m_PropertiesUI->SetScene(m_SceneUI);
        }
    }

    void EditorLayer::SaveScene()
    {
        if (m_CurrentFilepath.empty())
        {
            SaveSceneAs();
        }
        else
        {
            Serializer ser;
            ser.Serialize(m_Scene.get(), m_CurrentFilepath);
        }
    }

    void EditorLayer::SaveSceneAs()
    {
        std::string filepath = FileDialogs::SaveFile(
            "Lumi Scene (*.lumiscene)\0*.lumiscene\0");
        m_CurrentFilepath = filepath;
        if (!filepath.empty())
        {
            Serializer ser;
            ser.Serialize(m_Scene.get(), filepath);
        }
    }

    bool EditorLayer::OnKeyPressed(KeyPressedEvent& e)
    {
        bool ctrl = Input::IsKeyPressed(Key::LeftCtrl) ||
            Input::IsKeyPressed(Key::RightCtrl);
        bool shift = Input::IsKeyPressed(Key::LeftShift) ||
            Input::IsKeyPressed(Key::RightShift);

        switch (e.GetKeyCode())
        {
        case Key::N:
            if (ctrl)
                NewScene();
            break;
        case Key::O:
            if (ctrl)
                OpenScene();
            break;
        case Key::S:
            if (shift && ctrl)
                SaveSceneAs();
            else if (ctrl)
                SaveScene();
            break;
        case Key::Q:
            Application::Get().Close();
            break;
        default:
            break;
        }
        return false;
    }

    bool EditorLayer::OnMousePressed(MouseButtonPressedEvent& e)
    {
        return false;
    }
}