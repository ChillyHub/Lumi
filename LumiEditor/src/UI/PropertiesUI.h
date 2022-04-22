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
		bool DrawTransformVec(const std::string& label, glm::vec3& vec);
	private:
		std::shared_ptr<SceneUI> m_Scene;
		Entity* m_SelectedEntity = nullptr;
	};
}