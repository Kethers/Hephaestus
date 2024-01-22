#pragma once

#include "Hephaestus/Renderer/Pipeline.h"

#include "Vulkan.h"
#include "VulkanShader.h"

namespace Hep
{
	class VulkanPipeline : public Pipeline
	{
	public:
		VulkanPipeline(const PipelineSpecification& spec);
		~VulkanPipeline() override;

		PipelineSpecification& GetSpecification() override { return m_Specification; }
		const PipelineSpecification& GetSpecification() const override { return m_Specification; }

		void Invalidate() override;

		void Bind() override;

		VkPipeline GetVulkanPipeline() { return m_VulkanPipeline; }
		VkPipelineLayout GetVulkanPipelineLayout() { return m_PipelineLayout; }
		VkDescriptorSet GetDescriptorSet() { return m_DescriptorSet.DescriptorSets[0]; }

	private:
		PipelineSpecification m_Specification;

		VkPipelineLayout m_PipelineLayout;
		VkPipeline m_VulkanPipeline;
		VulkanShader::ShaderMaterialDescriptorSet m_DescriptorSet;
	};
}
