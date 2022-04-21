#pragma once

#include <Lumi.h>

#include "EditorCamera2D.h"
#include "EditorCamera3D.h"

namespace Lumi
{
	class EditorScene : public Scene
	{
	public:
		EditorScene();
		void EditorUpdate(Timestep ts);
		Camera& GetCamera2D();
		Camera& GetCamera3D();
		EditorCamera2D& GetCameraScript2D();
		EditorCamera3D& GetCameraScript3D();
	};
}