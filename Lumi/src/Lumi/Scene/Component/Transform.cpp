#include "pch.h"

#include "Transform.h"
#include "Lumi/Scene/Scene.h"

namespace Lumi
{
	glm::mat4 Transform::GetModelMatrix() const
	{
		return m_ModelMatrix;
	}

	void Transform::LookAt(const glm::vec3& worldPos, const glm::vec3& worldUp)
	{
		//glm::vec3 src = { 0.0f, 0.0f, -1.0f };
		//glm::vec3 right = { 1.0f, 0.0f, 0.0f };
		//glm::vec3 front = glm::normalize(worldPos - Position);
		//float cosAngle1 = glm::dot(src, front);
		//float w;
		//float n;
		//glm::vec3 axis1;
		//if (cosAngle1 < -0.999f)
		//{
		//	axis1 = glm::cross(src, { 0.0f, 0.0f, 1.0f });
		//	if (glm::length2(axis1) < 0.00001)
		//	{
		//		axis1 = glm::cross(src, { 1.0f, 0.0f, 0.0f });
		//	}
		//	w = 0.0f;
		//	n = 1.0f;
		//}
		//else
		//{
		//	axis1 = glm::cross(src, front);
		//	w = glm::sqrt((1 + cosAngle1) * 0.5f);
		//	n = glm::sqrt((1 - cosAngle1) * 0.5f);
		//}
		//axis1 = glm::normalize(axis1);
		//glm::quat r1 = glm::quat(w, n * axis1.x, n * axis1.y, n * axis1.z);
		//
		//glm::vec3 newFront = glm::rotate(r1, front);
		//glm::vec3 tmpRight = glm::rotate(r1, right);
		//glm::vec3 newRight = glm::normalize(glm::cross(newFront, worldUp));
		//float cosAngle2 = glm::dot(tmpRight, newRight);
		//glm::vec3 axis2;
		//if (cosAngle2 < -0.999f)
		//{
		//	axis2 = glm::cross(tmpRight, { 0.0f, 0.0f, 1.0f });
		//	if (glm::length2(axis2) < 0.00001)
		//	{
		//		axis2 = glm::cross(tmpRight, { 1.0f, 0.0f, 0.0f });
		//	}
		//	w = 0.0f;
		//	n = 1.0f;
		//}
		//else
		//{
		//	axis2 = glm::cross(tmpRight, newRight);
		//	w = glm::sqrt((1 + cosAngle2) * 0.5f);
		//	n = glm::sqrt((1 - cosAngle2) * 0.5f);
		//}
		//axis2 = glm::normalize(axis2);
		//glm::quat r2 = glm::quat(w, n * axis2.x, n * axis2.y, n * axis2.z);
		//
		//Rotation = r2 * r1;

		Rotation = glm::toQuat(glm::transpose(glm::lookAt(Position, worldPos, worldUp)));
	}

	void Transform::RotateAroundPoint(const glm::vec3& worldPos, const glm::vec3& axis, float angle)
	{
		glm::vec3 position = Position;
		glm::quat q = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
		q = glm::rotate(q, glm::radians(angle), axis);
		glm::vec3 newPosition = glm::rotate(q, position);
		Position = newPosition;
		LookAt(worldPos);
	}
	
	void Transform::OnUpdate(Timestep ts)
	{
		glm::mat4 model(1.0f);
		model = glm::translate(model, Position);
		model = glm::scale(model, Scale);
		glm::mat4 R = glm::mat4_cast(Rotation);
		m_ModelMatrix = model * R;
	}
}