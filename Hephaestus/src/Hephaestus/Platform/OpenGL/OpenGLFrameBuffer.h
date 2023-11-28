#pragma once
#include "Hephaestus/Renderer/FrameBuffer.h"

namespace Hep
{
	class OpenGLFramebuffer : public Framebuffer
	{
	public:
		OpenGLFramebuffer(uint32_t width, uint32_t height, FramebufferFormat format);
		~OpenGLFramebuffer() override;

		void Resize(uint32_t width, uint32_t height) override;

		void Bind() const override;
		void Unbind() const override;

		void BindTexture(uint32_t slot = 0) const override;

		RendererID GetRendererID() const override { return m_RendererID; }
		RendererID GetColorAttachmentRendererID() const override { return m_ColorAttachment; }
		RendererID GetDepthAttachmentRendererID() const override { return m_DepthAttachment; }

		virtual uint32_t GetWidth() const { return m_Width; }
		virtual uint32_t GetHeight() const { return m_Height; }
		virtual FramebufferFormat GetFormat() const { return m_Format; }

	private:
		RendererID m_RendererID = 0;
		uint32_t m_Width, m_Height;
		FramebufferFormat m_Format;

		RendererID m_ColorAttachment, m_DepthAttachment;
	};
}
