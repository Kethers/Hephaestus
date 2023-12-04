#pragma once
#include "Hephaestus/Renderer/FrameBuffer.h"

namespace Hep
{
	class OpenGLFramebuffer : public Framebuffer
	{
	public:
		OpenGLFramebuffer(const FramebufferSpecification& spec);
		~OpenGLFramebuffer() override;

		void Resize(uint32_t width, uint32_t height) override;

		void Bind() const override;
		void Unbind() const override;

		void BindTexture(uint32_t slot = 0) const override;

		RendererID GetRendererID() const override { return m_RendererID; }
		RendererID GetColorAttachmentRendererID() const override { return m_ColorAttachment; }
		RendererID GetDepthAttachmentRendererID() const override { return m_DepthAttachment; }

		const FramebufferSpecification& GetSpecification() const override { return m_Specification; }

	private:
		FramebufferSpecification m_Specification;
		RendererID m_RendererID = 0;

		RendererID m_ColorAttachment = 0, m_DepthAttachment = 0;
	};
}
