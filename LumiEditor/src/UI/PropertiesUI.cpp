#include <Lumi.h>
#include <imgui.h>

#include "PropertiesUI.h"

namespace Lumi
{
	PropertiesUI::PropertiesUI(const std::shared_ptr<SceneUI>& scene)
	{
		SetScene(scene);
	}

	void PropertiesUI::SetScene(const std::shared_ptr<SceneUI>& scene)
	{
		m_Scene = scene;
	}

	void PropertiesUI::OnImGuiRender()
	{
		ImGui::Begin("Properties");

		if (m_Scene->m_SelectedEntity)
		{
			DrawComponents(m_Scene->m_SelectedEntity);
		}

		ImGui::End();
	}

	void PropertiesUI::DrawComponents(Entity* entity)
	{
		auto& name = entity->Name;

		char buffer[256];
		memset(buffer, 0, sizeof(buffer));
		strcpy_s(buffer, sizeof(buffer), name.c_str());
		if (ImGui::InputText("Name", buffer, sizeof(buffer)))
		{
			name = std::string(buffer);
		}
		ImGui::Separator();

		if (ImGui::TreeNodeEx((void*)typeid(Transform).hash_code(),
			ImGuiTreeNodeFlags_DefaultOpen, "Transform"))
		{
			auto& transform = entity->GetComponent<Transform>();
			auto eularAngle = glm::eulerAngles(transform.Rotation);
			eularAngle = glm::degrees(eularAngle);
			ImGui::DragFloat3("Position", glm::value_ptr(transform.Position), 0.1f);
			if (ImGui::DragFloat3("Rotation", glm::value_ptr(eularAngle), 0.1f))
			{
				transform.Rotation = glm::quat(glm::radians(eularAngle));
			}
			ImGui::DragFloat3("Scale", glm::value_ptr(transform.Scale), 0.1f);
			
			ImGui::TreePop();
			ImGui::Separator();
		}
		
		if (entity->HasComponent<Camera>())
		{
			if (ImGui::TreeNodeEx((void*)typeid(Camera).hash_code(),
				ImGuiTreeNodeFlags_DefaultOpen, "Camera"))
			{
				auto& camera = entity->GetComponent<Camera>();

				ImGui::TreePop();
				ImGui::Separator();
			}
		}

		if (entity->HasComponent<Material2D>())
		{
			if (ImGui::TreeNodeEx((void*)typeid(Material2D).hash_code(),
				ImGuiTreeNodeFlags_DefaultOpen, "Material2D"))
			{
				auto& material = entity->GetComponent<Material2D>();
				ImGui::ColorEdit3("Color", glm::value_ptr(material.QuadColor));

				ImGui::TreePop();
				ImGui::Separator();
			}
		}

		if (entity->HasComponent<Script>())
		{
			if (ImGui::TreeNodeEx((void*)typeid(Script).hash_code(),
				ImGuiTreeNodeFlags_DefaultOpen, "Script"))
			{
				auto& material = entity->GetComponent<Script>();

				ImGui::TreePop();
				ImGui::Separator();
			}
		}
	}
}