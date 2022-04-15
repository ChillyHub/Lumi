#pragma once

#include "pch.h"

#include "Lumi/Scene/Component/Component.h"
#include "Lumi/Scene/Scene.h"

#include <entt.hpp>

namespace Lumi
{
	class Entity
	{
	public:
		std::string Name;
	public:
		Entity() = default;
		Entity(const Entity& e) = default;
		Entity(entt::entity entity, Scene* scene, std::string& name)
			: m_Entity(entity), m_Scene(scene), Name(name) {}

		template <typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			T& component = m_Scene->GetRegistry().emplace<T>(m_Entity, std::forward<Args>(args)...);
			return component;
		}

		template <typename T>
		T& GetComponent()
		{
			return m_Scene->GetRegistry().get<T>(m_Entity);
		}

		template <typename T, typename... Args>
		decltype(auto) GetComponents()
		{
			return m_Scene->GetRegistry().get<T, Args>(m_Entity);
		}

		template <typename T, typename... Args>
		void RemoveComponent()
		{
			m_Scene->GetRegistry().remove<T, Args>(m_Entity);
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
		entt::entity m_Entity { entt::null };
		Scene* m_Scene { nullptr };
	};
}