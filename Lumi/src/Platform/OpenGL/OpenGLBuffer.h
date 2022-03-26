#pragma once

#include "Lumi/Renderer/Buffer.h"

namespace Lumi
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, unsigned int size);
		OpenGLVertexBuffer(unsigned int size);
		virtual ~OpenGLVertexBuffer();

		virtual unsigned int GetSize() const override { return m_Size; }
		virtual const BufferLayout& GetLayout() const override { return m_Layout; }
		virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }
		virtual void SetData(const void* data, unsigned int size);

		virtual void Bind() const override;
		virtual void Unbind() const override;
	private:
		unsigned int m_VBO;
		unsigned int m_Size;
		BufferLayout m_Layout;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(unsigned int* indices, unsigned int count);
		virtual ~OpenGLIndexBuffer();

		virtual unsigned int GetCount() const override { return m_Count; }

		virtual void Bind() const override;
		virtual void Unbind() const override;
	private:
		unsigned int m_EBO;
		unsigned int m_Count;
	};
}
