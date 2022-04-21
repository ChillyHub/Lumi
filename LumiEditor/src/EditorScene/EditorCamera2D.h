#pragma once

#include <Lumi.h>
#include <imgui.h>

namespace Lumi
{
	class EditorCamera2D : public Script
	{
	public:
		EditorCamera2D(const EditorCamera2D& src) = default;
		EditorCamera2D(Entity * ent) : Script(ent) {}
	private:
		float m_MouseMovedSensitivity = 0.002f;
		float m_MouseScaleSensitivity = 0.25f;
		float m_CursorPosX = 0.0f;
		float m_CursorPosY = 0.0f;
	public:
		bool IsHovered = true;
	public:
		void Start()
		{
			
		}

		void Update(Timestep ts)
		{
			auto& transform = entity->transform;

			float X = Input::GetCursorX();
			float Y = Input::GetCursorY();

			if ((Input::IsMouseButtonPressed(Mouse::Middle) || 
				Input::IsMouseButtonPressed(Mouse::Right)) &&
				IsHovered)
			{
				auto& camera = entity->GetComponent<Camera>();
				
				float deltaX = X - m_CursorPosX;
				float deltaY = Y - m_CursorPosY;
				deltaX = deltaX / camera.ScreenHeight * camera.Size;
				deltaY = deltaY / camera.ScreenHeight * camera.Size;

				auto deltaPos = -glm::vec3(deltaX, -deltaY, 0.0f);
				
				transform.Position += deltaPos;
			}

			m_CursorPosX = X;
			m_CursorPosY = Y;
		}
	};
}