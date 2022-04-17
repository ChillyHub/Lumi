#include "EditorScene.h"

namespace Lumi
{
	EditorScene::EditorScene() : Scene()
	{
		CreateEntity("EditorCamera2D");
	}

	void EditorScene::EditorUpdate(Timestep ts)
	{
		auto view = GetRegistry().view<Transform>();
		for (auto e : view)
		{
			auto [transform] = view.get(e);
			transform.OnUpdate(ts);
			//camera.OnUpdate(ts);
		}
	}
}