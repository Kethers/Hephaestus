#pragma once

#include "Hephaestus/Renderer/Framebuffer.h"

#include "Vulkan.h"

#include "VulkanImage.h"

namespace Hep
{
	class VulkanFramebuffer : public Framebuffer
	{
	public:
		VulkanFramebuffer(const FramebufferSpecification& spec);
		~VulkanFramebuffer() override;

		void Resize(uint32_t width, uint32_t height, bool forceRecreate = false) override;
		void AddResizeCallback(const std::function<void(Ref<Framebuffer>)>& func) override;

		void Bind() const override {}
		void Unbind() const override {}

		void BindTexture(uint32_t attachmentIndex = 0, uint32_t slot = 0) const override {}

		uint32_t GetWidth() const override { return m_Width; }
		uint32_t GetHeight() const override { return m_Height; }
		RendererID GetRendererID() const override { return m_RendererID; }
		virtual RendererID GetColorAttachmentRendererID() const { return 0; }
		virtual RendererID GetDepthAttachmentRendererID() const { return 0; }

		Ref<Image2D> GetImage(uint32_t attachmentIndex = 0) const override
		{
			HEP_CORE_ASSERT(attachmentIndex < m_Attachments.size());
			return m_Attachments[attachmentIndex];
		}
		Ref<Image2D> GetDepthImage() const override { return m_DepthAttachment; }
		size_t GetColorAttachmentCount() const { return m_Attachments.size(); }
		VkRenderPass GetRenderPass() const { return m_RenderPass; }
		VkFramebuffer GetVulkanFramebuffer() const { return m_Framebuffer; }
		const std::vector<VkClearValue>& GetVulkanClearValues() const { return m_ClearValues; }

		const FramebufferSpecification& GetSpecification() const override { return m_Specification; }

	private:
		FramebufferSpecification m_Specification;
		RendererID m_RendererID = 0;
		uint32_t m_Width = 0, m_Height = 0;

		std::vector<Ref<Image2D>> m_Attachments;
		Ref<Image2D> m_DepthAttachment;

		std::vector<VkClearValue> m_ClearValues;

		VkSampler m_ColorAttachmentSampler;
		VkRenderPass m_RenderPass = nullptr;
		VkFramebuffer m_Framebuffer = nullptr;

		std::vector<std::function<void(Ref<Framebuffer>)>> m_ResizeCallbacks;
	};
}
