#pragma once

#include "pch.h"

#include "Buffer.h"

namespace Lumi
{
	class VertexArray
	{
	public:
		virtual ~VertexArray() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) = 0;
		virtual void AddIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) = 0;

		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffer() const = 0;
		virtual const std::shared_ptr<IndexBuffer> GetIndexBuffer() const = 0;
		virtual unsigned int GetVertexCount() const = 0;

		static std::shared_ptr<VertexArray> Create();
	};
}
