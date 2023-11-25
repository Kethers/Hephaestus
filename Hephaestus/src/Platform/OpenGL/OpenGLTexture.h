#pragma once

#include "Hephaestus/Renderer/Texture.h"

namespace Hep
{
	class OpenGLTexture2D : public Hep::Texture2D
	{
	public:
		OpenGLTexture2D(const std::string path);
		~OpenGLTexture2D() override;

		uint32_t GeiWidth() const override { return m_Width; }
		uint32_t GeiHeight() const override { return m_Height; }

		void Bind(uint32_t slot = 0) const override;

	private:
		std::string m_Path;
		uint32_t m_Width, m_Height;
		uint32_t m_RendererID;
	};
}
