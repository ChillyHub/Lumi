#include "EditorScene.h"

namespace Lumi
{
	EditorScene::EditorScene() : Scene()
	{
		Name = "EditorScene";
		
		auto& entity2D = CreateEntity("EditorCamera2D");
		auto& camera2D = entity2D.AddComponent<Camera>();
		camera2D.Projection = ProjectionType::Orthographic;
		camera2D.entity->transform.Position = { 0.0f, 0.0f, 2.0f };
		entity2D.AddComponent<Script>().Bind<EditorCamera2D>();

		auto& entity3D = CreateEntity("EditorCamera3D");
		auto& camera3D = entity3D.AddComponent<Camera>();
		camera3D.entity->transform.Position = { 0.0f, 0.0f, 20.0f };
		entity3D.AddComponent<Script>().Bind<EditorCamera3D>();
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

	Camera& EditorScene::GetCamera3D()
	{
		return m_Entities[1]->GetComponent<Camera>();
	}

	EditorCamera2D& EditorScene::GetCameraScript2D()
	{
		return m_Entities[0]->GetComponent<Script>().GetInstance<EditorCamera2D>();
	}

	EditorCamera3D& EditorScene::GetCameraScript3D()
	{
		return m_Entities[1]->GetComponent<Script>().GetInstance<EditorCamera3D>();
	}
}