#pragma once

#include <Lumi.h>
#include <imgui.h>
#include <imgui_internal.h>

#include "SceneUI.h"

namespace Lumi
{
	class PropertiesUI
	{
	public:
		PropertiesUI() = default;
		PropertiesUI(const std::shared_ptr<SceneUI>& scene);

		void SetScene(const std::shared_ptr<SceneUI>& scene);
		void OnImGuiRender();
	private:
		void DrawComponents(Entity* entity);
		bool DrawTransformVec(const std::string& label, glm::vec3& vec);
	private:
		template <typename T, typename Func>
		void DrawComponent(const std::string& name, Entity* entity, Func func)
		{
			if (entity->HasComponent<T>())
			{
				auto flag = ImGuiTreeNodeFlags_AllowItemOverlap
					| ImGuiTreeNodeFlags_DefaultOpen 
					| ImGuiTreeNodeFlags_Framed
					| ImGuiTreeNodeFlags_SpanAvailWidth
					| ImGuiTreeNodeFlags_FramePadding;
				auto regionAvail = ImGui::GetContentRegionAvail();
				ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4, 4 });
				bool remove = false;
				bool open = ImGui::TreeNodeEx((void*)typeid(T).hash_code(),
					flag, name.c_str());
				float lineHeight = GImGui->Font->FontSize
					+ GImGui->Style.FramePadding.y * 2.0f;
				ImGui::PopStyleVar();
				ImGui::SameLine(regionAvail.x - lineHeight * 0.5f);
				if (ImGui::Button("X", ImVec2{ lineHeight, lineHeight }))
				{
					remove = true;
				}
				if (open)
				{
					auto& component = entity->GetComponent<T>();
					func(component);

					ImGui::TreePop();
					ImGui::Separator();
				}
				if (remove)
				{
					entity->RemoveComponent<T>();
				}
			}
		}
	private:
		std::shared_ptr<SceneUI> m_Scene;
	};
}