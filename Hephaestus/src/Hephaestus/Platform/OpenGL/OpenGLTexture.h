#pragma once

#include "Hephaestus//Renderer/RendererAPI.h"
#include "Hephaestus/Renderer/Texture.h"

namespace Hep
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(TextureFormat format, uint32_t width, uint32_t height, TextureWrap wrap);
		OpenGLTexture2D(const std::string& path, bool srgb);
		~OpenGLTexture2D() override;

		void Bind(uint32_t slot = 0) const override;

		TextureFormat GetFormat() const override { return m_Format; }
		uint32_t GetWidth() const override { return m_Width; }
		uint32_t GetHeight() const override { return m_Height; }
		// This function currently returns the expected number of mips based on image size,
		// not present mips in data
		uint32_t GetMipLevelCount() const override;

		void Lock() override;
		void Unlock() override;

		void Resize(uint32_t width, uint32_t height) override;
		Buffer GetWriteableBuffer() override;

		const std::string& GetPath() const override { return m_FilePath; }

		bool Loaded() const override { return m_Loaded; }

		RendererID GetRendererID() const override { return m_RendererID; }

		bool operator==(const Texture& other) const override
		{
			return m_RendererID == ((OpenGLTexture2D&)other).m_RendererID;
		}

	private:
		RendererID m_RendererID;
		TextureFormat m_Format;
		TextureWrap m_Wrap = TextureWrap::Clamp;
		uint32_t m_Width, m_Height;

		Buffer m_ImageData;
		bool m_IsHDR = false;

		bool m_Locked = false;
		bool m_Loaded = false;

		std::string m_FilePath;
	};

	class OpenGLTextureCube : public TextureCube
	{
	public:
		OpenGLTextureCube(TextureFormat format, uint32_t width, uint32_t height);
		OpenGLTextureCube(const std::string& path);
		~OpenGLTextureCube() override;

		void Bind(uint32_t slot = 0) const override;

		TextureFormat GetFormat() const override { return m_Format; }
		uint32_t GetWidth() const override { return m_Width; }
		uint32_t GetHeight() const override { return m_Height; }
		// This function currently returns the expected number of mips based on image size,
		// not present mips in data
		uint32_t GetMipLevelCount() const override;

		const std::string& GetPath() const override { return m_FilePath; }

		RendererID GetRendererID() const override { return m_RendererID; }

		bool operator==(const Texture& other) const override
		{
			return m_RendererID == ((OpenGLTextureCube&)other).m_RendererID;
		}

	private:
		RendererID m_RendererID;
		TextureFormat m_Format;
		uint32_t m_Width, m_Height;

		unsigned char* m_ImageData;

		std::string m_FilePath;
	};
}
