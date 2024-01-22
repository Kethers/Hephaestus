#pragma once

#include "Hephaestus/Renderer/RenderPass.h"

namespace Hep
{
	class VulkanRenderPass : public RenderPass
	{
	public:
		VulkanRenderPass(const RenderPassSpecification& spec);
		~VulkanRenderPass() override;

		RenderPassSpecification& GetSpecification() override { return m_Specification; }
		const RenderPassSpecification& GetSpecification() const override { return m_Specification; }

	private:
		RenderPassSpecification m_Specification;
	};
}
