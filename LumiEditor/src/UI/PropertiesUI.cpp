#include <Lumi.h>

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
		if (ImGui::InputText("##Name", buffer, sizeof(buffer)))
		{
			name = std::string(buffer);
		}
		ImGui::Separator();

		float lineHeight = GImGui->Font->FontSize
			+ GImGui->Style.FramePadding.y * 2.0f;
		float lineWidth = ImGui::GetContentRegionAvail().x;
		if (ImGui::Button("Add Component", ImVec2{ lineWidth, lineHeight }))
		{
			ImGui::OpenPopup("Add Component");
		}

		if (ImGui::BeginPopup("Add Component"))
		{
			if (ImGui::MenuItem("Camera"))
			{
				m_Scene->m_SelectedEntity->AddComponent<Camera>();
				ImGui::CloseCurrentPopup();
			}
			if (ImGui::MenuItem("Material2D"))
			{
				m_Scene->m_SelectedEntity->AddComponent<Material2D>();
				ImGui::CloseCurrentPopup();
			}
			if (ImGui::MenuItem("Script"))
			{
				m_Scene->m_SelectedEntity->AddComponent<Script>();
				ImGui::CloseCurrentPopup();
			}

			ImGui::EndPopup();
		}

		if (ImGui::TreeNodeEx((void*)typeid(Transform).hash_code(),
			ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed, "Transform"))
		{
			auto& transform = entity->GetComponent<Transform>();
			auto eularAngle = glm::eulerAngles(transform.Rotation);
			eularAngle = glm::degrees(eularAngle);
			DrawTransformVec("Position", transform.Position);
			if (DrawTransformVec("Rotation", eularAngle))
			{
				transform.Rotation = glm::quat(glm::radians(eularAngle));
			}
			DrawTransformVec("Scale", transform.Scale);
			
			ImGui::TreePop();
			ImGui::Separator();
		}

		DrawComponent<Camera>("Camera", entity, [](Camera& camera)
			{
				ImGui::Columns(2);
				ImGui::SetColumnWidth(0, 100.0f);

				ImGui::Text("Activated");
				ImGui::NextColumn();
				ImGui::Checkbox("##Activated", &camera.Activated);
				ImGui::NextColumn();

				const char* projectTypes[] = { "Perspective", "Orthogtaphic" };
				const char* currentType = projectTypes[(int)camera.Projection];
				ImGui::Text("Projection");
				ImGui::NextColumn();
				if (ImGui::BeginCombo("##Projection", currentType))
				{
					for (int i = 0; i < 2; i++)
					{
						bool isSelected = currentType == projectTypes[i];
						if (ImGui::Selectable(projectTypes[i], isSelected))
						{
							currentType = projectTypes[i];
							camera.Projection = (ProjectionType)i;
						}

						if (isSelected)
						{
							ImGui::SetItemDefaultFocus();
						}
					}

					ImGui::EndCombo();
				}
				ImGui::NextColumn();

				if (camera.Projection == ProjectionType::Perspective)
				{
					ImGui::Text("FOV");
					ImGui::NextColumn();
					ImGui::DragFloat("##FOV", &camera.Zoom, 1.0f, 1.0f, 170.0f);
					ImGui::NextColumn();

					ImGui::Text("Aspect");
					ImGui::NextColumn();
					ImGui::DragFloat("##Aspect", &camera.Aspect, 0.001f, 0.001f);
					ImGui::NextColumn();

					ImGui::Text("Near Clip");
					ImGui::NextColumn();
					ImGui::DragFloat("##Near Clip", &camera.NearClip, 0.01f, 0.0f);
					ImGui::NextColumn();

					ImGui::Text("Far Clip");
					ImGui::NextColumn();
					ImGui::DragFloat("##Far Clip", &camera.FarClip, 0.1f, 0.0f);
				}

				else if (camera.Projection == ProjectionType::Orthographic)
				{
					ImGui::Text("Size");
					ImGui::NextColumn();
					ImGui::DragFloat("##Size", &camera.Size, 0.01f, 0.001f);
					ImGui::NextColumn();

					ImGui::Text("Aspect");
					ImGui::NextColumn();
					ImGui::DragFloat("##Aspect", &camera.Aspect, 0.001f, 0.001f);
					ImGui::NextColumn();

					ImGui::Text("Near Clip");
					ImGui::NextColumn();
					ImGui::DragFloat("##Near Clip", &camera.NearClip, 0.01f, 0.0f);
					ImGui::NextColumn();

					ImGui::Text("Far Clip");
					ImGui::NextColumn();
					ImGui::DragFloat("##Far Clip", &camera.FarClip, 0.1f, 0.0f);
					ImGui::NextColumn();
				}

				ImGui::Columns(1);
			});

		DrawComponent<Material2D>("Material2D", entity, [](Material2D& material)
			{
				ImGui::Columns(2);
				ImGui::SetColumnWidth(0, 100.0f);
				ImGui::Text("Color");
				ImGui::NextColumn();
				
				ImGui::ColorEdit4("##Color", glm::value_ptr(material.QuadColor));
				ImGui::Columns(1);
			});

		DrawComponent<Script>("Script", entity, [](Script& script)
			{
				ImGui::Columns(2);
				ImGui::SetColumnWidth(0, 100.0f);
				ImGui::Text("Activated");
				ImGui::NextColumn();

				ImGui::Checkbox("##Activated", &script.Activated);
				ImGui::Columns(1);
			});
	}

	bool PropertiesUI::DrawTransformVec(const std::string& label, glm::vec3& vec)
	{
		auto& io = ImGui::GetIO();
		auto boldFont = io.Fonts->Fonts[1];
		
		ImGui::PushID(label.c_str());
		
		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, 100.0f);
		ImGui::Text(label.c_str());
		ImGui::NextColumn();

		ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

		float height = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 buttonSize = { height + 3.0f, height };

		float resetValue = 0.0f;
		bool change = false;

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.96f, 0.32f, 0.07f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 1.0f, 0.42f, 0.17f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.96f, 0.32f, 0.07f, 1.0f });
		ImGui::PushFont(boldFont);
		ImGui::Button("X", buttonSize);
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		if (ImGui::DragFloat("##X", &vec.x, 0.1f))
		{
			change = true;
		}
		ImGui::PopItemWidth();

		ImGui::SameLine();
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.48f, 0.73f, 0.0f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.58f, 0.83f, 0.1f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.48f, 0.73f, 0.0f, 1.0f });
		ImGui::PushFont(boldFont);
		ImGui::Button("Y", buttonSize);
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		if (ImGui::DragFloat("##Y", &vec.y, 0.1f))
		{
			change = true;
		}
		ImGui::PopItemWidth();

		ImGui::SameLine();
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.0f, 0.63f, 0.94f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.1f, 0.73f, 1.0f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.0f, 0.63f, 0.94f, 1.0f });
		ImGui::PushFont(boldFont);
		ImGui::Button("Z", buttonSize);
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		if (ImGui::DragFloat("##Z", &vec.z, 0.1f))
		{
			change = true;
		}
		ImGui::PopItemWidth();

		ImGui::PopStyleVar();
		ImGui::Columns(1);

		ImGui::PopID();

		return change;
	}
}