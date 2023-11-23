#include "heppch.h"
#include "Buffer.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Hep
{
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
			{
				HEP_CORE_ASSERT(false, "RendererAPI::API::None is currently not supported!");
				return nullptr;
			}
			case RendererAPI::API::OpenGL: return new OpenGLVertexBuffer(vertices, size);
		}

		HEP_CORE_ASSERT(false, "Unknown Renderer API!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
			{
				HEP_CORE_ASSERT(false, "RendererAPI::API::None is currently not supported!");
				return nullptr;
			}
			case RendererAPI::API::OpenGL: return new OpenGLIndexBuffer(indices, size);
		}

		HEP_CORE_ASSERT(false, "Unknown Renderer API!");
		return nullptr;
	}
}
