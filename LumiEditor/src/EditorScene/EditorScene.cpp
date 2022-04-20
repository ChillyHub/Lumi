#include "EditorScene.h"
#include "EditorCamera2D.h"

namespace Lumi
{
	EditorScene::EditorScene() : Scene()
	{
		auto& entity = CreateEntity("EditorCamera2D");
		auto& camera = entity.AddComponent<Camera>();
		camera.Projection = ProjectionType::Orthographic;
		camera.entity->transform.Position = { 0.0f, 0.0f, 2.0f };
		entity.AddComponent<Script>().Bind<EditorCamera2D>();
	}

	void EditorScene::EditorUpdate(Timestep ts)
	{
		auto group = GetRegistry().group<Transform, Camera, Script>();
		for (auto e : group)
		{
			auto [transform, camera, script] = group.get(e);
			if (script.Activated)
			{
				if (!script)
				{
					script.Init();
				}
				script.OnUpdate(ts);
			}
			if (camera.Activated)
			{
				camera.OnUpdate(ts);
			}
			transform.OnUpdate(ts);
		}
	}

	Camera& EditorScene::GetCamera2D()
	{
		return m_Entities[0]->GetComponent<Camera>();
	}
}