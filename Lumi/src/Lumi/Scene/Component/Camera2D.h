#pragma once

#include "Component.h"
#include "Lumi/Scene/Component/Transform.h"

#include <glm/glm.hpp>

namespace Lumi
{
	class Camera2D : public Component
	{
	public:
		bool Activated = true;
		ProjectionType Projection = ProjectionType::Perspective;

		// camera options
		float MovementSpeed = 2.5f;
		// projection base
		float Zoom = 45.0f;
		float NearClip = 0.1f;
		float FarClip = 1000.0f;
		int Width = 1920;
		int Height = 1080;
	};
}