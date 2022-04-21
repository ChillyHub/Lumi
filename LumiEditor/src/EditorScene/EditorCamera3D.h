#pragma once

#include <Lumi.h>

namespace Lumi
{
	class EditorCamera3D : public Script
	{
	public:
		EditorCamera3D(const EditorCamera3D& src) = default;
		EditorCamera3D(Entity* ent) : Script(ent) {}
	private:
		float m_MouseMovedSensitivity = 0.002f;
		float m_MouseScaleSensitivity = 0.25f;
		float m_CursorPosX = 0.0f;
		float m_CursorPosY = 0.0f;
		glm::vec3 m_FocalPos = { 0.0f, 0.0f, 0.0f };
	public:
		void Start()
		{

		}

		void Update(Timestep ts)
		{
			auto& transform = entity->transform;

			float X = Input::GetCursorX();
			float Y = Input::GetCursorY();

			if (Input::IsMouseButtonPressed(Mouse::Middle))
			{
				auto& camera = entity->GetComponent<Camera>();
				auto& transform = camera.entity->transform;

				float deltaX = X - m_CursorPosX;
				float deltaY = Y - m_CursorPosY;
				glm::vec3 delta = { deltaX, -deltaY, 0.0f };
				auto up = glm::rotate(transform.Rotation, delta);

				if (Input::IsKeyPressed(Key::LeftShift))
				{
					up = up / camera.ScreenHeight * camera.Size;
					auto deltaPos = -glm::vec3(up.x, up.y, 0.0f);

					transform.Position += deltaPos;
					m_FocalPos += deltaPos;
				}
				else if (glm::length2(up) != 0)
				{
					up = glm::normalize(up);
					auto back = glm::rotate(transform.Rotation, { 0.0f, 0.0f, 1.0f });
					auto axis = glm::normalize(glm::cross(up, back));
					float angle = glm::length(delta) / 3.0f;

					transform.RotateAroundPoint(m_FocalPos, axis, angle);
				}
			}

			m_CursorPosX = X;
			m_CursorPosY = Y;
		}
	};
}