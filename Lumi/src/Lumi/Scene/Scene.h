#pragma once

#include "Lumi/Core/Timestep.h"
#include "Lumi/Scene/Component/Component.h"
#include "Lumi/Scene/Component/Material2D.h"
#include "Lumi/Scene/Component/Transform.h"
#include "Lumi/Scene/Component/Transform2D.h"

#include <entt.hpp>
#include <glm/glm.hpp>

namespace Lumi
{
	class Entity;

	class Scene
	{
	public:
		Entity CreateEntity(std::string name = "Entity");
		Entity CreateEntity2D(std::string name = "Entity");
		entt::registry& GetRegistry() { return m_Registry; }
		void OnUpdate2D(Timestep ts, glm::vec3 color);
	private:
		entt::registry m_Registry;
	};
}