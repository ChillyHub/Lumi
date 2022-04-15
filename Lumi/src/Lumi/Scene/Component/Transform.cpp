#include "pch.h"

#include "Transform.h"

namespace Lumi
{
	void Transform::OnUpdate(Timestep ts)
	{
		glm::mat4 model(1.0f);
		model = glm::translate(model, Position);
		model = glm::scale(model, Scale);
		glm::mat4 R = glm::mat4_cast(Rotation);
		m_ModelMatrix = model * R;
	}
}