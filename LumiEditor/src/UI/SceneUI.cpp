#include <Lumi.h>
#include <imgui.h>

#include "SceneUI.h"

namespace Lumi
{
	SceneUI::SceneUI(const std::shared_ptr<Scene>& context)
	{
		SetContext(context);
	}

	void SceneUI::SetContext(const std::shared_ptr<Scene>& context)
	{
		m_Context = context;
	}

	void SceneUI::SetEditor(const std::shared_ptr<EditorScene>& editor)
	{
		m_Editor = editor;
	}

	void SceneUI::OnImGuiRender()
	{
		ImGui::Begin("Scene Collection");

		//m_Context->GetRegistry().each([&](auto ent)
		//	{
		//		Entity entity{ ent, m_Context.get() };
		//		std::string name = entity.GetComponent<Transform>().entity->Name;
		//		ImGui::Text(name.c_str());
		//	});

		//ImGuiTreeNodeFlags flag = (m_Context.get() == m_SelectedScene ?
		//	ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
		auto opened = ImGui::TreeNodeEx((void*)0,
			ImGuiTreeNodeFlags_DefaultOpen, m_Context->Name.c_str());
		if (ImGui::IsItemClicked())
		{
			m_SelectedScene = m_Context.get();
		}
		if (opened)
		{
			auto view = m_Context->GetRegistry().view<Transform>();
			for (auto v : view)
			{
				auto entity = m_Context->GetRegistry().get<Transform>(v).entity;
				DrawEntityNodes(entity);
			}
			ImGui::TreePop();
		}

		opened = ImGui::TreeNodeEx((void*)1,
			ImGuiTreeNodeFlags_DefaultOpen, m_Editor->Name.c_str());
		if (ImGui::IsItemClicked())
		{
			m_SelectedScene = m_Editor.get();
		}
		if (opened)
		{
			auto view = m_Editor->GetRegistry().view<Transform>();
			for (auto v : view)
			{
				auto entity = m_Editor->GetRegistry().get<Transform>(v).entity;
				DrawEntityNodes(entity);
			}
			ImGui::TreePop();
		}

		ImGui::End();
	}

	void SceneUI::DrawEntityNodes(Entity* entity)
	{
		ImGuiTreeNodeFlags flag = (entity == m_SelectedEntity ?
			ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
		auto opened = ImGui::TreeNodeEx((void*)(uint64_t)(unsigned int)*entity, 
			flag, entity->Name.c_str());
		if (ImGui::IsItemClicked())
		{
			m_SelectedEntity = entity;
		}
		if (opened)
		{
			ImGui::TreePop();
		}
	}
}