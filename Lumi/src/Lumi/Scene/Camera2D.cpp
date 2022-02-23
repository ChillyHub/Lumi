#include "pch.h"
#include "Camera2D.h"

namespace Lumi
{

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	Camera2D::Camera2D(int width, int height, glm::vec3 position)
		: m_Width(width), m_Height(height), m_Position(position)
	{
		UpdateView();
		UpdateProjection();
	}

	void Camera2D::OnUpdate(Timestep ts)
	{
		
	}

	void Camera2D::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_EVENT_FN(Camera2D::OnMouseButtonPressed));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(BIND_EVENT_FN(Camera2D::OnMouseButtonRealeased));
		dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FN(Camera2D::OnScrolleMouse));
		dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENT_FN(Camera2D::OnMoveCursorPos));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(Camera2D::OnResizeWindow));
		
	}

	void Camera2D::UpdateView()
	{
		glm::mat4 rota(1.0f);
		glm::vec3 up(0.0f, 1.0f, 0.0f);
		rota = glm::rotate(rota, glm::radians(m_Rotation), { 0.0f, 0.0f, 1.0f });
		m_ViewMatrix = glm::lookAt(m_Position, m_Position + glm::vec3(0.0f, 0.0f, -1.0f), glm::mat3(rota) * up);
	}

	void Camera2D::UpdateProjection()
	{
		if (m_ProjectionType == ProjectionType::Perspective)
			m_ProjectMatrix = glm::perspective(m_Zoom, (float)m_Width / (float)m_Height, m_NearClip, m_FarClip);
		else
			m_ProjectMatrix = glm::ortho(-(float)m_Width / (float)m_Height * m_OrthoScale, 
				(float)m_Width / (float)m_Height * m_OrthoScale, 
				-m_OrthoScale, m_OrthoScale, -500.0f, 500.0f);
	}

	bool Camera2D::OnMouseButtonPressed(MouseButtonPressedEvent& e)
	{
		if (e.GetMouseButton() == LUMI_MOUSE_BUTTON_MIDDLE)
			m_MouseButtonMiddlePressed = true;
		if (e.GetMouseButton() == LUMI_MOUSE_BUTTON_RIGHT)
			m_MouseButtonRightPressed = true;
		
		return false;
	}

	bool Camera2D::OnMouseButtonRealeased(MouseButtonReleasedEvent& e)
	{
		if (e.GetMouseButton() == LUMI_MOUSE_BUTTON_MIDDLE)
			m_MouseButtonMiddlePressed = false;
		if (e.GetMouseButton() == LUMI_MOUSE_BUTTON_RIGHT)
			m_MouseButtonRightPressed = false;

		return false;
	}

	bool Camera2D::OnScrolleMouse(MouseScrolledEvent& e)
	{
		if (m_OrthoScale > 0.05f || e.GetOffsetY() < 0)
			m_ScaleOffset += e.GetOffsetY() * m_MouseScaleSensitivity;

		// if (m_ScaleOffset < 0.0f)
		// 	m_OrthoScale = std::exp(0.95f * -m_ScaleOffset);
		// else
		// 	m_OrthoScale = 0.05f + 0.95f / (m_ScaleOffset + 1);

		m_OrthoScale = std::max(std::exp(0.7f * -m_ScaleOffset), 0.05f);
		
		UpdateProjection();

		return false;
	}

	bool Camera2D::OnMoveCursorPos(MouseMovedEvent& e)
	{
		if (m_MouseButtonMiddlePressed)
		{
			float deltaX = (float)e.GetX() - m_CursorPosX;
			float deltaY = (float)e.GetY() - m_CursorPosY;

			glm::mat4 rota(1.0f);
			glm::vec3 up(0.0f, 1.0f, 0.0f);
			rota = glm::rotate(rota, glm::radians(m_Rotation), { 0.0f, 0.0f, 1.0f });

			auto deltaPos = -(glm::mat3(rota) * glm::vec3(deltaX, -deltaY, 0.0f));

			m_Position = m_Position + deltaPos * m_OrthoScale * (2.0f / m_Height);
			UpdateView();
		}
		if (m_MouseButtonRightPressed)
		{
			float deltaX = (float)e.GetX() - m_CursorPosX;

			m_Rotation += deltaX * m_MouseMovedSensitivity * 10;
			UpdateView();
		}
		m_CursorPosX = e.GetX();
		m_CursorPosY = e.GetY();

		return false;
	}

	bool Camera2D::OnResizeWindow(WindowResizeEvent& e)
	{
		m_Width = (int)e.GetWidth();
		m_Height = (int)e.GetHeight();
		UpdateProjection();

		return false;
	}
}