#include "pch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Lumi
{
	static GLenum ShaderDataType2OpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Bool:
			return GL_BOOL;
		case ShaderDataType::Int:
		case ShaderDataType::Int2:
		case ShaderDataType::Int3:
		case ShaderDataType::Int4:
			return GL_INT;
		case ShaderDataType::Float:
		case ShaderDataType::Float2:
		case ShaderDataType::Float3:
		case ShaderDataType::Float4:
		case ShaderDataType::Mat3:
		case ShaderDataType::Mat4:
			return GL_FLOAT;
		default:
			break;
		}

		LUMI_CORE_ASSERT(false, "Unknown shader data type!");
		return GL_NONE;
	}

	/////////////////////////////////////////////////////////////////////
	// class OpenGLVertexArray
	// -----------------------
	
	OpenGLVertexArray::OpenGLVertexArray()
	{
		glGenVertexArrays(1, &m_VAO);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_VAO);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_VAO);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		LUMI_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(),
			"Vertex buffer has not layout data!");
		
		glBindVertexArray(m_VAO);
		vertexBuffer->Bind();

		unsigned int index = 0;
		const auto& elements = vertexBuffer->GetLayout();
		for (const auto& e : elements)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				e.GetElementCount(),
				ShaderDataType2OpenGLBaseType(e.Type),
				e.Normalized ? GL_TRUE : GL_FALSE,
				elements.GetVertexSize(),
				(const void*)(unsigned long long)e.Offset);
			index++;
		}

		m_VertexBuffer.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::AddIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_VAO);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}
}