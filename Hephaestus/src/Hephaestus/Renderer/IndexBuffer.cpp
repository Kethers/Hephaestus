#include "heppch.h"
#include "IndexBuffer.h"

#include "Renderer.h"

#include "Hephaestus/Platform/OpenGL/OpenGLIndexBuffer.h"
#include "Hephaestus/Platform/Vulkan/VulkanIndexBuffer.h"

#include "Hephaestus/Renderer/RendererAPI.h"

namespace Hep
{
	Ref<IndexBuffer> IndexBuffer::Create(uint32_t size)
	{
		switch (RendererAPI::Current())
		{
			// @formatter:off
			case RendererAPIType::None:		return nullptr;
			case RendererAPIType::OpenGL:	return Ref<OpenGLIndexBuffer>::Create(size);
			case RendererAPIType::Vulkan:	return Ref<VulkanIndexBuffer>::Create(size);
			// @formatter:on
		}
		HEP_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(void* data, uint32_t size)
	{
		switch (RendererAPI::Current())
		{
			// @formatter:off
			case RendererAPIType::None:		return nullptr;
			case RendererAPIType::OpenGL:	return Ref<OpenGLIndexBuffer>::Create(data, size);
			case RendererAPIType::Vulkan:	return Ref<VulkanIndexBuffer>::Create(data, size);
			// @formatter:on
		}
		HEP_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}
