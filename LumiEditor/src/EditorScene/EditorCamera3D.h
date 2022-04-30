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
		float m_ScaleOffset = 0.0f;
		glm::vec3 m_FocalPoint = { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_OldPosition = { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_CameraUp = { 0.0f, 0.0f, 1.0f };
		glm::vec3 tmpRight = { 1.0f, 0.0f, 0.0f };
	public:
		bool IsHovered = true;
		bool IsFocused = true;
	public:
		void Start()
		{
			auto& transform = entity->transform;
			m_OldPosition = transform.Position;
			transform.LookAt(m_FocalPoint);
		}

		void Update(Timestep ts)
		{
			auto& transform = entity->transform;

			float X = Input::GetCursorX();
			float Y = Input::GetCursorY();
			auto& camera = entity->GetComponent<Camera>();

			if (Input::IsMouseButtonPressed(Mouse::Middle) && IsHovered)
			{
				float deltaX = X - m_CursorPosX;
				float deltaY = Y - m_CursorPosY;
				glm::vec3 delta = { deltaX, -deltaY, 0.0f };
				auto up = glm::rotate(transform.Rotation, delta);

				if (Input::IsKeyPressed(Key::LeftShift))
				{
					auto mat = camera.GetWorldToClipMatrix();
					auto mat_inv = glm::inverse(mat);
					auto clipPoint = mat * glm::vec4(m_FocalPoint, 1.0f);
					auto screenDelta = glm::vec4(delta.x / camera.ScreenWidth,
						delta.y / camera.ScreenHeight, 0.0f, 0.0f) 
						* clipPoint.w * 2.0f;
					auto worldPoint = mat_inv * (clipPoint + screenDelta);
					auto worldDelta = glm::vec3(worldPoint) - m_FocalPoint;

					transform.Position -= worldDelta;
					m_FocalPoint -= worldDelta;
				}
				else if (glm::length2(up) != 0)
				{
					float angleX = delta.x / 4.0f;
					float angleY = delta.y / 4.0f;
					transform.RotateAroundPoint(m_FocalPoint,
						{ 0.0f, 0.0f, 1.0f }, -angleX);
					transform.LookAt(m_FocalPoint, m_CameraUp);
					auto cameraBack = glm::rotate(transform.Rotation,
						{ 0.0f, 0.0f, 1.0f });
					auto planeBack = glm::vec3(cameraBack.x, cameraBack.y, 0.0f);
					auto oldDot = glm::dot(transform.Position - m_FocalPoint,
						planeBack);
					auto cameraUp = glm::rotate(transform.Rotation,
						{ 0.0f, 1.0f, 0.0f });
					auto cameraRight = glm::rotate(transform.Rotation,
						{ 1.0f, 0.0f, 0.0f });
					transform.RotateAroundPoint(m_FocalPoint,
						cameraRight, angleY);
					auto newDot = glm::dot(transform.Position - m_FocalPoint,
						planeBack);
					if (oldDot * newDot < 0)
					{
						m_CameraUp = -m_CameraUp;
					}
					transform.LookAt(m_FocalPoint, m_CameraUp);
				}
				m_OldPosition = transform.Position;
			}
			else if (transform.Position != m_OldPosition)
			{
				auto deltaOnWorld = transform.Position - m_OldPosition;
				auto cameraX = glm::rotate(transform.Rotation, { 0.0f, 1.0f, 0.0f });
				auto cameraY = glm::rotate(transform.Rotation, { 1.0f, 0.0f, 0.0f });
				auto dCameraX = glm::dot(cameraX, deltaOnWorld) * cameraX;
				auto dCameraY = glm::dot(cameraY, deltaOnWorld) * cameraY;
				m_FocalPoint += dCameraX + dCameraY;
				m_OldPosition = transform.Position;
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
			if (!Input::IsMouseButtonPressed(Mouse::Middle) && 
				(IsHovered || IsFocused))
			{
				auto& transform = entity->transform;
				auto& camera = entity->GetComponent<Camera>();

				auto back = glm::rotate(transform.Rotation, { 0.0f, 0.0f, 1.0f });
				auto dist = glm::length(transform.Position - m_FocalPoint) * 0.2f;
				transform.Position += -e.GetOffsetY() * dist * back;

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