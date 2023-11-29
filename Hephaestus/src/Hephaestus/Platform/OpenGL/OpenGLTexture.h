#pragma once

#include "Hephaestus//Renderer/RendererAPI.h"
#include "Hephaestus/Renderer/Texture.h"

namespace Hep
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(TextureFormat format, unsigned int width, unsigned int height, TextureWrap wrap);
		OpenGLTexture2D(const std::string& path, bool srgb);
		~OpenGLTexture2D() override;

		void Bind(uint32_t slot = 0) const override;

		TextureFormat GetFormat() const override { return m_Format; }
		uint32_t GetWidth() const override { return m_Width; }
		uint32_t GetHeight() const override { return m_Height; }

		void Lock() override;
		void Unlock() override;

		void Resize(uint32_t width, uint32_t height) override;
		Buffer GetWriteableBuffer() override;

		const std::string& GetPath() const override { return m_FilePath; }

		RendererID GetRendererID() const override { return m_RendererID; }

	private:
		RendererID m_RendererID;
		TextureFormat m_Format;
		TextureWrap m_Wrap = TextureWrap::Clamp;
		uint32_t m_Width, m_Height;

		Buffer m_ImageData;

		bool m_Locked = false;

		std::string m_FilePath;
	};

	class OpenGLTextureCube : public TextureCube
	{
	public:
		OpenGLTextureCube(const std::string& path);
		~OpenGLTextureCube() override;

		void Bind(uint32_t slot = 0) const override;

		TextureFormat GetFormat() const override { return m_Format; }
		uint32_t GetWidth() const override { return m_Width; }
		uint32_t GetHeight() const override { return m_Height; }

		const std::string& GetPath() const override { return m_FilePath; }

		RendererID GetRendererID() const override { return m_RendererID; }

	private:
		RendererID m_RendererID;
		TextureFormat m_Format;
		unsigned int m_Width, m_Height;

		unsigned char* m_ImageData;

		std::string m_FilePath;
	};
}
