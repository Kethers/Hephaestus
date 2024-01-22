#pragma once
#include "Hephaestus/Renderer/FrameBuffer.h"

namespace Hep
{
	class OpenGLFramebuffer : public Framebuffer
	{
	public:
		OpenGLFramebuffer(const FramebufferSpecification& spec);
		~OpenGLFramebuffer() override;

		void Resize(uint32_t width, uint32_t height, bool forceRecreate = false) override;
		void AddResizeCallback(const std::function<void(Ref<Framebuffer>)>& func) override {}

		void Bind() const override;
		void Unbind() const override;

		void BindTexture(uint32_t attachmentIndex = 0, uint32_t slot = 0) const override;

		Ref<Image2D> GetImage(uint32_t attachmentIndex = 0) const override
		{
			HEP_CORE_ASSERT(attachmentIndex < m_ColorAttachments.size());
			return m_ColorAttachments[attachmentIndex];
		}
		Ref<Image2D> GetDepthImage() const override { return m_DepthAttachment; }

		uint32_t GetWidth() const override { return m_Width; }
		uint32_t GetHeight() const override { return m_Height; }

		RendererID GetRendererID() const override { return m_RendererID; }
		RendererID GetColorAttachmentRendererID(int index = 0) const { return m_ColorAttachments[index]; }
		RendererID GetDepthAttachmentRendererID() const { return m_DepthAttachment; }

		const FramebufferSpecification& GetSpecification() const override { return m_Specification; }

	private:
		FramebufferSpecification m_Specification;
		RendererID m_RendererID = 0;

		std::vector<Ref<Image2D>> m_ColorAttachments;
		Ref<Image2D> m_DepthAttachment;

		std::vector<ImageFormat> m_ColorAttachmentFormats;
		ImageFormat m_DepthAttachmentFormat = ImageFormat::None;

		uint32_t m_Width = 0, m_Height = 0;
	};
}
