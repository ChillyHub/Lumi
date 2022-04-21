#pragma once

#include "Lumi/Core/Timestep.h"
#include "Lumi/Scene/Component/Component.h"

#include <entt.hpp>
#include <glm/glm.hpp>

namespace Lumi
{
	class Entity;

	class Scene
	{
		friend class Entity;
		friend class PropertiesUI;
	public:
		std::string Name;
	public:
		Scene(std::string name = "Scene") : Name(name) {}
		Entity& CreateEntity(std::string name = "Entity");
		entt::registry& GetRegistry() { return m_Registry; }
		virtual void OnUpdate2D(Timestep ts, glm::vec3 color);

		bool operator==(const Scene& rhs) const { return Name == rhs.Name; }
		bool operator!=(const Scene& rhs) const { return !(*this == rhs); }
	protected:
		std::vector<std::shared_ptr<Entity>> m_Entities;
		entt::registry m_Registry;
	};
}