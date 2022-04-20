#include "pch.h"
#include "Scene.h"

#include "Lumi/Renderer/Renderer2D.h"
#include "Lumi/Scene/Component/Material2D.h"
#include "Lumi/Scene/Component/Script.h"
#include "Lumi/Scene/Component/Transform.h"

namespace Lumi
{
	Entity& Scene::CreateEntity(std::string name)
	{
		auto ptr = std::shared_ptr<Entity>(
			new Entity{ m_Registry.create(), this, name });
		m_Entities.push_back(ptr);
		return *m_Entities.back();
	}
	
	void Scene::OnUpdate2D(Timestep ts, glm::vec3 color)
	{
		m_Registry.view<Script>().each([=](auto entity, Script& script)
			{
				if (script.Activated)
				{
					if (!script)
					{
						script.Init();
					}
					
					script.OnUpdate(ts);
				}
			});
		
		auto group = m_Registry.group<Transform, Material2D>();
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