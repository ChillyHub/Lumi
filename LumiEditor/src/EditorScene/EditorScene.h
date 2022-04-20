#pragma once

#include <Lumi.h>

namespace Lumi
{
	class EditorScene : public Scene
	{
	public:
		EditorScene();
		void EditorUpdate(Timestep ts);
		Camera& GetCamera2D();
	};
}