#include "heppch.h"
#include "Pipeline.h"

#include "Renderer.h"

#include "Hephaestus/Platform/OpenGL/OpenGLPipeline.h"
#include "Hephaestus/Platform/Vulkan/VulkanPipeline.h"

#include "Hephaestus/Renderer/RendererAPI.h"

namespace Hep
{
	Ref<Pipeline> Pipeline::Create(const PipelineSpecification& spec)
	{
		switch (RendererAPI::Current())
		{
			// @formatter:off
			case RendererAPIType::None:		return nullptr;
			case RendererAPIType::OpenGL:	return Ref<OpenGLPipeline>::Create(spec);
			case RendererAPIType::Vulkan:	return Ref<VulkanPipeline>::Create(spec);
			// @formatter:on
		}
		HEP_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}
