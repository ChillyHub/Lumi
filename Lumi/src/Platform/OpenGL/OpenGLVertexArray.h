#pragma once

#include "Lumi/Renderer/VertexArray.h"

namespace Lumi
{
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>&vertexBuffer) override;
		virtual void AddIndexBuffer(const std::shared_ptr<IndexBuffer>&indexBuffer) override;

		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffer() const override
		{
			return m_VertexBuffer;
		}
		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const override
		{
			return m_IndexBuffer;
		}
		virtual unsigned int GetVertexCount() const override
		{
			unsigned int layoutSize = m_VertexBuffer.begin()->get()->GetLayout().GetVertexSize();
			LUMI_CLIENT_ASSERT(layoutSize, "Vertex buffer has not layout data!");
			
			unsigned int size = m_VertexBuffer.begin()->get()->GetSize();
			return size / layoutSize;
		}
	private:
		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffer;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
		unsigned int m_VAO;
	};
}
