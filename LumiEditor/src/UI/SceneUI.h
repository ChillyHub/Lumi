#pragma once

#include <Lumi.h>

#include <EditorScene/EditorScene.h>

namespace Lumi
{
	class SceneUI
	{
		friend class PropertiesUI;
	public:
		SceneUI() = default;
		SceneUI(const std::shared_ptr<Scene>& context);

		void Reset() { m_SelectedEntity = nullptr; }
		void SetContext(const std::shared_ptr<Scene>& contest);
		void SetEditor(const std::shared_ptr<EditorScene>& editor);
		void OnImGuiRender();
	private:
		void DrawEntityNodes(Entity* entity);
	private:
		std::shared_ptr<Scene> m_Context;
		std::shared_ptr<EditorScene> m_Editor;
		Entity* m_SelectedEntity = nullptr;
		Scene* m_SelectedScene = nullptr;
	};
}