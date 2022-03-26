#pragma once

namespace Lumi
{
	enum class ShaderDataType
	{
		None = 0, Bool,
		Int, Int2, Int3, Int4,
		Float, Float2, Float3, Float4,
		Mat3, Mat4
	};

	static unsigned int ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Bool:
			return 1;
		case ShaderDataType::Int:
		case ShaderDataType::Float:
			return 4;
		case ShaderDataType::Int2:
		case ShaderDataType::Float2:
			return 8;
		case ShaderDataType::Int3:
		case ShaderDataType::Float3:
			return 12;
		case ShaderDataType::Int4:
		case ShaderDataType::Float4:
			return 16;
		case ShaderDataType::Mat3:
			return 36;
		case ShaderDataType::Mat4:
			return 64;
		default:
			break;
		}

		LUMI_CORE_ASSERT(false, "Unknown shader data type!");
		return 0;
	}

	struct BufferElement
	{
		std::string Name;
		ShaderDataType Type;
		unsigned int Size;
		unsigned int Offset;
		bool Normalized;

		BufferElement(const std::string& name, ShaderDataType type, bool normalized = false)
			: Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
		{

		}

		unsigned int GetElementCount() const
		{
			switch (Type)
			{
			case ShaderDataType::Bool:
			case ShaderDataType::Int:
			case ShaderDataType::Float:
				return 1;
			case ShaderDataType::Int2:
			case ShaderDataType::Float2:
				return 2;
			case ShaderDataType::Int3:
			case ShaderDataType::Float3:
				return 3;
			case ShaderDataType::Int4:
			case ShaderDataType::Float4:
				return 4;
			case ShaderDataType::Mat3:
				return 9;
			case ShaderDataType::Mat4:
				return 16;
			default:
				break;
			}

			LUMI_CORE_ASSERT(false, "Unknown shader data type!");
			return 0;
		}
	};

	class BufferLayout
	{
	public:
		BufferLayout() = default;

		BufferLayout(std::initializer_list<BufferElement> element)
			: m_Elements(element), m_VertexSize(0)
		{
			CalculateOffsetAndVertexSize();
		}

		const std::vector<BufferElement>& GetElements() const { return m_Elements; }
		const unsigned int GetVertexSize() const { return m_VertexSize; }

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.cbegin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.cend(); }
	private:
		std::vector<BufferElement> m_Elements;
		unsigned int m_VertexSize = 0;

		void CalculateOffsetAndVertexSize()
		{
			unsigned int offset = 0;
			for (auto& e : m_Elements)
			{
				e.Offset = offset;
				offset += e.Size;
				m_VertexSize += e.Size;
			}
		}
	};
	
	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default;

		virtual unsigned int GetSize() const = 0;
		virtual const BufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual void SetData(const void* data, unsigned int size) = 0;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static std::shared_ptr<VertexBuffer> Create(unsigned int size);
		static std::shared_ptr<VertexBuffer> Create(float* vertices, unsigned int size);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() = default;

		virtual unsigned int GetCount() const = 0;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static std::shared_ptr<IndexBuffer> Create(unsigned int* indices, unsigned int count);
	};
}
