#pragma once

#include <glm/glm.hpp>

namespace Lumi
{
	class Camera
	{
	public:
		Camera(const glm::mat4 projection = glm::mat4(1.0f)) 
			: m_ProjectMatrix(projection) { }

		virtual ~Camera() = default;

		const glm::mat4& GetProjectMatrix() const { return m_ProjectMatrix; }
	protected:
		glm::mat4 m_ProjectMatrix;
	};
}