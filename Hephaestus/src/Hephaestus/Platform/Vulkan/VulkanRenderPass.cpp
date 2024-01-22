#include "heppch.h"
#include "VulkanRenderPass.h"

namespace Hep
{
	VulkanRenderPass::VulkanRenderPass(const RenderPassSpecification& spec)
		: m_Specification(spec)
	{
	}

	VulkanRenderPass::~VulkanRenderPass()
	{
	}
}
