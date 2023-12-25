#include "heppch.h"

#include "Renderer.h"

#include "Hephaestus/Platform/OpenGL/OpenGLVertexBuffer.h"

namespace Hep
{
	Ref<VertexBuffer> VertexBuffer::Create(void* data, uint32_t size, VertexBufferUsage usage)
	{
		switch (RendererAPI::Current())
		{
			// @formatter:off
			case RendererAPIType::None:		return nullptr;
			case RendererAPIType::OpenGL:	return Ref<OpenGLVertexBuffer>::Create(data, size, usage);
			// @formatter:on
		}
		HEP_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

	Ref<VertexBuffer> VertexBuffer::Create(uint32_t size, VertexBufferUsage usage)
	{
		switch (RendererAPI::Current())
		{
			// @formatter:off
			case RendererAPIType::None:		return nullptr;
			case RendererAPIType::OpenGL:	return Ref<OpenGLVertexBuffer>::Create(size, usage);
			// @formatter:on
		}
		HEP_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}
