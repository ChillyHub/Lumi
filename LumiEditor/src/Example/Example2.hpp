#pragma once

#include <Lumi.h>

namespace Lumi
{
	class Example2 : public Script
	{
	public:
		Example2(const Example2& src) = default;
		Example2(Entity* ent) : Script(ent) {}
	public:
		glm::vec4 QuadColor = { 0.113f, 0.226f, 0.339f, 1.0f };
	public:
		void Start()
		{
			auto& material = entity->AddComponent<Material2D>();
			material.Texture2D = nullptr;
			material.QuadColor = QuadColor;
		}

		void Update(Timestep ts)
		{
			
		}
	};
}