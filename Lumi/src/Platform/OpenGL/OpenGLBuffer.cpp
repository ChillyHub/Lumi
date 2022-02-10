#include "pch.h"
#include "OpenGLBuffer.h"

#include <glad/glad.h>

namespace Lumi
{
	/////////////////////////////////////////////////////////////////////
	// class OpenGLVertexBuffer
	// ------------------------

	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, unsigned int size)
		: m_Size(size)
	{
		// ** vertices here is just a pointer (8 byte), sizeof(vertices) = 8, it will be unused.
		glGenBuffers(1, &m_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(unsigned int size)
		: m_Size(size)
	{
		glGenBuffers(1, &m_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, size, NULL, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &m_VBO);
	}

	void OpenGLVertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	}

	void OpenGLVertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	/////////////////////////////////////////////////////////////////////
	// class OpenGLIndexBuffer
	// -----------------------

	OpenGLIndexBuffer::OpenGLIndexBuffer(unsigned int* indices, unsigned int count)
		: m_Count(count)
	{
		glGenBuffers(1, &m_EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * count, indices, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &m_EBO);
	}

	void OpenGLIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	}

	void OpenGLIndexBuffer::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}