#pragma once

#include <Lumi.h>

namespace Lumi
{
	class SceneUI
	{
		friend class PropertiesUI;
	public:
		SceneUI() = default;
		SceneUI(const std::shared_ptr<Scene>& context);

		void SetContext(const std::shared_ptr<Scene>& contest);
		void OnImGuiRender();
	private:
		void DrawEntityNodes(Entity* entity);
	private:
		std::shared_ptr<Scene> m_Context;
		Entity* m_SelectedEntity = nullptr;
		Scene* m_SelectedScene = nullptr;
	};
}