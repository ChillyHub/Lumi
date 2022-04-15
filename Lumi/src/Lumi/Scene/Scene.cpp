#include "pch.h"
#include "Scene.h"

#include "Lumi/Renderer/Renderer2D.h"
#include "Lumi/Scene/Entity.h"

namespace Lumi
{
	Entity Scene::CreateEntity(std::string name)
	{
		Entity entity = { m_Registry.create(), this, name };
		entity.AddComponent<Transform>();
		return entity;
	}

	Entity Scene::CreateEntity2D(std::string name)
	{
		Entity entity = { m_Registry.create(), this, name };
		entity.AddComponent<Transform2D>();
		return entity;
	}
	
	void Scene::OnUpdate2D(Timestep ts, glm::vec3 color)
	{
		auto group = m_Registry.group<Transform2D, Material2D>();
		for (auto entity : group)
		{
			auto [transform, material] = group.get(entity);

			Renderer2D::DrawQuad(material.Texture2D,
				transform.Position,
				transform.Scale,
				material.QuadColor,
				transform.Rotation);
		}
	}
}