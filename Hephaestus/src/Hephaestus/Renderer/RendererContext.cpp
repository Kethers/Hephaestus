#include "heppch.h"
#include "RendererContext.h"

#include "Hephaestus/Renderer/RendererAPI.h"

#include "Hephaestus/Platform/OpenGL/OpenGLContext.h"
#include "Hephaestus/Platform/Vulkan/VulkanContext.h"

namespace Hep
{
	Ref<RendererContext> RendererContext::Create(GLFWwindow* windowHandle)
	{
		switch (RendererAPI::Current())
		{
			case RendererAPIType::None: return nullptr;
			case RendererAPIType::OpenGL: return Ref<OpenGLContext>::Create(windowHandle);
			case RendererAPIType::Vulkan: return Ref<VulkanContext>::Create(windowHandle);
		}
		HEP_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}
