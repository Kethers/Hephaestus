#include "heppch.h"
#include "OpenGLVertexArray.h"

#include "glad/glad.h"

#include "Hephaestus/Renderer/Renderer.h"

namespace Hep
{
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float: return GL_FLOAT;
			case ShaderDataType::Float2: return GL_FLOAT;
			case ShaderDataType::Float3: return GL_FLOAT;
			case ShaderDataType::Float4: return GL_FLOAT;
			case ShaderDataType::Mat3: return GL_FLOAT;
			case ShaderDataType::Mat4: return GL_FLOAT;
			case ShaderDataType::Int: return GL_INT;
			case ShaderDataType::Int2: return GL_INT;
			case ShaderDataType::Int3: return GL_INT;
			case ShaderDataType::Int4: return GL_INT;
			case ShaderDataType::Bool: return GL_BOOL;
		}

		HEP_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		HEP_RENDER_S({
			glCreateVertexArrays(1, &self->m_RendererID);
			});
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		HEP_RENDER_S({
			glDeleteVertexArrays(1, &self->m_RendererID);
			});
	}

	void OpenGLVertexArray::Bind() const
	{
		HEP_RENDER_S({
			glBindVertexArray(self->m_RendererID);
			});
	}

	void OpenGLVertexArray::Unbind() const
	{
		HEP_RENDER_S({
			glBindVertexArray(0);
			});
	}

	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		HEP_CORE_ASSERT(!vertexBuffer->GetLayout().GetElements().empty(), "Vertex Buffer has no layout!");

		Bind();
		vertexBuffer->Bind();

		HEP_RENDER_S1(vertexBuffer,
			{
			const auto& layout = vertexBuffer->GetLayout();
			for (const auto& element : layout)
			{
			auto glBaseType = ShaderDataTypeToOpenGLBaseType(element.Type);
			glEnableVertexAttribArray(self->m_VertexBufferIndex);
			if (glBaseType == GL_INT)
			{
			glVertexAttribIPointer(self->m_VertexBufferIndex,
				element.GetComponentCount(),
				glBaseType,
				layout.GetStride(),
				(const void*)(intptr_t)element.Offset);
			}
			else
			{
			glVertexAttribPointer(self->m_VertexBufferIndex,
				element.GetComponentCount(),
				glBaseType,
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)(intptr_t)element.Offset);
			}
			self->m_VertexBufferIndex++;
			}
			});
		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		Bind();
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}
}
