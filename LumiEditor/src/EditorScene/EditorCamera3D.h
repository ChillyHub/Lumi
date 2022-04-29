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
		glm::vec3 camUp = { 0.0f, 0.0f, 1.0f };
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
					//up = up / camera.ScreenHeight * camera.Size;
					//auto deltaPos = -glm::vec3(up.x, up.y, 0.0f);
					//
					//transform.Position += deltaPos;
					//m_FocalPoint += deltaPos;

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
					//up = glm::normalize(up);
					//auto camUp = glm::rotate(transform.Rotation, { 0.0f, 1.0f, 0.0f });
					//auto back = glm::rotate(transform.Rotation, { 0.0f, 0.0f, 1.0f });
					//auto axis = glm::normalize(glm::cross(up, back));
					//float angle = glm::length(delta) / 4.0f;
					//
					//transform.RotateAroundPoint(m_FocalPoint, axis, angle, camUp);

					//up = glm::normalize(up);
					//auto right = glm::rotate(transform.Rotation, { 1.0f, 0.0f, 0.0f });
					//auto camUp = glm::rotate(transform.Rotation, { 0.0f, 1.0f, 0.0f });
					//auto back = glm::rotate(transform.Rotation, { 0.0f, 0.0f, 1.0f });
					//auto a1 = right.x; auto a2 = camUp.x;
					//auto b1 = right.y; auto b2 = camUp.y;
					//if (a2 - b2 == 0)
					//{
					//	camUp = glm::normalize(camUp);
					//}
					//else
					//{
					//	auto pxy = transform.Position.x + transform.Position.y;
					//	auto B = (a1 - b1 + pxy) / (b2 - a2);
					//	camUp = glm::normalize(right + B * camUp);
					//}
					//auto axis = glm::normalize(glm::cross(up, back));
					//float angle = glm::length(delta) / 4.0f;
					//transform.RotateAroundPoint(m_FocalPoint, axis, angle);
					//transform.LookAt(m_FocalPoint, camUp);

					up = glm::normalize(up);
					auto theUp = glm::rotate(transform.Rotation, { 0.0f, 1.0f, 0.0f });
					auto back = glm::rotate(transform.Rotation, { 0.0f, 0.0f, 1.0f });
					auto backXY = glm::normalize(glm::vec3{ back.x, back.y, 0.0f });
					auto oldPos = glm::normalize(transform.Position - m_FocalPoint);
					auto oldXY = glm::normalize(glm::vec3{ oldPos.x, oldPos.y, 0.0f });
					auto axis = glm::normalize(glm::cross(up, back));
					float angle = glm::length(delta) / 4.0f;
					transform.RotateAroundPoint(m_FocalPoint, axis, angle);
					auto newPos = glm::normalize(transform.Position - m_FocalPoint);
					auto newXY = glm::normalize(glm::vec3{ newPos.x, newPos.y, 0.0f });
					if (glm::length2(backXY) == 0)
					{
						if (glm::dot(theUp, newXY) > 0)
						{
							camUp = -camUp;
						}
					}
					else if (glm::dot(backXY, oldXY) > 0 && glm::dot(backXY, newXY) < 0)
					{
						camUp = -camUp;
					}
					//auto r = transform.Position - m_FocalPoint;
					//auto ro = glm::vec3{ -r.x, -r.y, 0.0f };
					//glm::vec3 right;
					//if (glm::length2(ro) < 0.001f)
					//{
					//	right = tmpRight;
					//}
					//else if (r.z > 0)
					//{
					//	right = glm::normalize(glm::cross(ro, r));
					//}
					//else if (r.z < 0)
					//{
					//	right = glm::normalize(glm::cross(r, ro));
					//}
					//else
					//{
					//	right = glm::normalize(glm::cross({ 0.0f, 0.0f, 1.0f }, ro));
					//}
					//auto camUps = glm::normalize(glm::cross(r, tmpRight));
					transform.LookAt(m_FocalPoint, camUp);
					//tmpRight = glm::rotate(transform.Rotation, { 1.0f, 0.0f, 0.0f });

					//auto back = glm::rotate(transform.Rotation, { 0.0f, 0.0f, 1.0f });
					//auto ndot = glm::dot(back, { 0.0f, 0.0f, 1.0f });
					//glm::vec3 axisXY;
					//if (ndot * ndot > 0.99f)
					//{
					//	axisXY = tmpRight;
					//}
					//else
					//{
					//	axisXY = glm::normalize(glm::cross({ 0.0f, 0.0f, 1.0f, back }));
					//	tmpRight = axisXY;
					//}

					//auto axisXY = glm::rotate(transform.Rotation, { 1.0f, 0.0f, 0.0f });
					//float angleXY = delta.y / 4.0f;
					//transform.RotateAroundPoint(m_FocalPoint, axisXY, angleXY);
					//auto camUp = transform.Position - m_OldPosition;
					//auto axisZ = glm::vec3{ 0.0f, 0.0f, 1.0f };
					//float angleZ = delta.x / 4.0f;
					//transform.RotateAroundPoint(m_FocalPoint, axisZ, angleZ);
					//transform.LookAt(m_FocalPoint, camUp);

					//auto back = glm::rotate(transform.Rotation, { 0.0f, 0.0f, 1.0f });
					//glm::vec3 axisXY;
					//glm::vec3 camUp = { 0.0f, 0.0f, 1.0f };
					//if (glm::dot(camUp, back) > 0.999f)
					//{
					//	axisXY = glm::rotate(transform.Rotation, { 0.0f, 1.0f, 0.0f });
					//}
					//else
					//{
					//	axisXY = glm::normalize(glm::cross({ 0.0f, 0.0f, 1.0f }, back));
					//}
					//auto camUp = glm::normalize(glm::cross(back, axisXY));
					//float angleXY = delta.y / 4.0f;
					//transform.RotateAroundPoint(m_FocalPoint, axisXY, angleXY, camUp);
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
			if (!Input::IsMouseButtonPressed(Mouse::Middle) && IsHovered)
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