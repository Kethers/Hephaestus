#include "heppch.h"
#include "RenderPass.h"

#include "Renderer.h"

#include "Hephaestus/Platform/OpenGL/OpenGLRenderPass.h"
#include "Hephaestus/Platform/Vulkan/VulkanRenderPass.h"

#include "Hephaestus/Renderer/RendererAPI.h"

namespace Hep
{
	Ref<RenderPass> RenderPass::Create(const RenderPassSpecification& spec)
	{
		switch (RendererAPI::Current())
		{
			case RendererAPIType::None: HEP_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
				return nullptr;
			case RendererAPIType::Vulkan: return Ref<VulkanRenderPass>::Create(spec);
			case RendererAPIType::OpenGL: return Ref<OpenGLRenderPass>::Create(spec);
		}

		HEP_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
