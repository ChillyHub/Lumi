#pragma once

#include "pch.h"

#include "Lumi/Scene/Component/Component.h"
#include "Lumi/Scene/Scene.h"
#include "Lumi/Scene/Component/Transform.h"

#include <entt.hpp>

namespace Lumi
{
	class Entity
	{
	public:
		std::string Name;
		Transform& transform;
	public:
		Entity(const Entity& src);
		Entity(entt::entity entity, Scene* scene, std::string name = "Entity")
			: m_Entity(entity), m_Scene(scene), Name(name), transform(AddTransform(scene, entity)) {}

		template <typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			if (HasComponent<T>())
			{
				return GetComponent<T>();
			}
			return m_Scene->GetRegistry().emplace<T>(m_Entity, this, std::forward<Args>(args)...);
		}

		template <typename T>
		T& GetComponent()
		{
			LUMI_CORE_ASSERT(HasComponent<T>(), "No Component {0}", typeid(T).name());
			return m_Scene->GetRegistry().get<T>(m_Entity);
		}

		template <typename T, typename... Args>
		decltype(auto) GetComponents()
		{
			LUMI_CORE_ASSERT((HasComponents<T, Args...>()), "No Components {0} ...", typeid(T).name());
			return m_Scene->GetRegistry().get<T, Args...>(m_Entity);
		}

		template <typename T>
		bool HasComponent()
		{
			return m_Scene->GetRegistry().all_of<T>(m_Entity);
		}

		template <typename T, typename... Args>
		bool HasComponents()
		{
			return m_Scene->GetRegistry().all_of<T, Args...>(m_Entity);
		}

		template <typename T, typename... Args>
		void RemoveComponent()
		{
			m_Scene->GetRegistry().remove<T, Args...>(m_Entity);
		}

		bool operator==(const Entity& rhs) const
		{
			return m_Scene == rhs.m_Scene && m_Entity == rhs.m_Entity;
		}

		bool operator!=(const Entity& rhs) const
		{
			return !(*this == rhs);
		}

		operator bool() const { return m_Entity != entt::null; }
		operator unsigned int() const { return (unsigned int)m_Entity; }
	private:
		Transform& AddTransform(Scene* scene, entt::entity entity)
		{
			return scene->GetRegistry().emplace<Transform>(entity, this);
		}
	private:
		entt::entity m_Entity { entt::null };
		Scene* m_Scene { nullptr };
	};
}