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
		float m_ScaleOffset = 0.0f;
	public:
		bool IsHovered = true;
		bool IsFocused = true;
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

		bool OnMouseButtonPressed(MouseButtonPressedEvent& e)
		{
			return false;
		}

		bool OnMouseButtonRealeased(MouseButtonReleasedEvent& e)
		{
			return false;
		}

		bool OnScrolleMouse(MouseScrolledEvent& e)
		{
			if (!Input::IsMouseButtonPressed(Mouse::Middle) && IsHovered)
			{
				auto& transform = entity->transform;
				auto& camera = entity->GetComponent<Camera>();
				
				if (camera.Size > 0.05f || e.GetOffsetY() < 0)
					m_ScaleOffset += e.GetOffsetY() * m_MouseScaleSensitivity;

				camera.Size = std::max(std::exp(0.7f * -m_ScaleOffset), 0.05f);
			}
			return false;
		}

		bool OnMoveCursorPos(MouseMovedEvent& e)
		{
			return false;
		}

		bool OnResizeWindow(WindowResizeEvent& e)
		{
			return false;
		}
	};
}