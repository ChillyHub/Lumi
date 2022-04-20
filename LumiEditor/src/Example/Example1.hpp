#pragma once

#include <Lumi.h>

namespace Lumi
{
	class Example1 : public Script
	{
	public:
		Example1(const Example1& src) = default;
		Example1(Entity* ent) : Script(ent) {}
	public:
		glm::vec4 QuadColor = { 0.113f, 0.113f, 0.113f, 1.0f };
	private:
		std::shared_ptr<Texture> quadTexture1;
		std::shared_ptr<Texture> quadTexture2;
		std::shared_ptr<Texture> quadTexture3;
		std::shared_ptr<Texture> quadTexture4;
		std::shared_ptr<Texture> quadTexture5;
		std::vector<std::shared_ptr<Texture>> textures;
	public:
		void Start()
		{
			entity->AddComponent<Material2D>();

			ResourceManager::LoadTexture2D("assets/textures/barbara2.png", "Barbara", true);
			ResourceManager::LoadTexture2D("assets/textures/bronya2.png", "Bronya", true);
			ResourceManager::LoadTexture2D("assets/textures/ei.png", "Ei", true);
			ResourceManager::LoadTexture2D("assets/textures/ganyu_keqing.png", "Ganyu", true);
			ResourceManager::LoadTexture2D("assets/textures/keqing.png", "Keqing", true);

			quadTexture1 = ResourceManager::GetTexture2D("Barbara");
			quadTexture2 = ResourceManager::GetTexture2D("Bronya");
			quadTexture3 = ResourceManager::GetTexture2D("Ei");
			quadTexture4 = ResourceManager::GetTexture2D("Ganyu");
			quadTexture5 = ResourceManager::GetTexture2D("Keqing");
			textures = { quadTexture1, quadTexture2, quadTexture3, quadTexture4, quadTexture5 };

		}

		void Update(Timestep ts)
		{
			auto [transform, material] =
				entity->GetComponents<Transform, Material2D>();
			
			for (float x = 0.0f, i = 0.0f; x < 50.0f; x += 1.2f)
			{
				for (float y = 0.0f; y < 50.0f; y += 1.2f, i++)
				{
					auto texture = textures[(int)i % textures.size()];

					transform.Position = { x, y, -0.01f };
					transform.Scale = { 1.0f, 1.0f, 1.0f };
					transform.Rotation = { 1.0f, 0.0f, 0.0f, 0.0f };
					material.Texture2D = nullptr;
					material.QuadColor = QuadColor;
					Renderer2D::DrawQuad(material.Texture2D,
						transform.Position,
						transform.Scale,
						material.QuadColor,
						transform.Rotation);

					transform.Position = { x, y, 0.0f };
					transform.Scale = { 1.0f, 1.0f, 1.0f };
					transform.Rotation = { 1.0f, 0.0f, 0.0f, 0.0f };
					material.Texture2D = texture;
					material.QuadColor = glm::vec4(1.0f);
					Renderer2D::DrawQuad(material.Texture2D,
						transform.Position,
						transform.Scale,
						material.QuadColor,
						transform.Rotation);
				}
			}
		}
	};
}