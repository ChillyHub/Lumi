#pragma once

#include <Lumi.h>

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
	private:
		std::shared_ptr<SceneUI> m_Scene;
		Entity* m_SelectedEntity = nullptr;
	};
}