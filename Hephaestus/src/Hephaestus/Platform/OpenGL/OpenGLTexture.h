#pragma once

#include "Hephaestus//Renderer/RendererTypes.h"
#include "Hephaestus/Renderer/Texture.h"

namespace Hep
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(ImageFormat format, uint32_t width, uint32_t height, const void* data, TextureProperties properties);
		OpenGLTexture2D(const std::string& path, TextureProperties properties);
		~OpenGLTexture2D() override;

		void Bind(uint32_t slot = 0) const override;

		Ref<Image2D> GetImage() const override { return m_Image; }

		ImageFormat GetFormat() const override { return m_Image->GetFormat(); }
		uint32_t GetWidth() const override { return m_Width; }
		uint32_t GetHeight() const override { return m_Height; }
		// This function currently returns the expected number of mips based on image size,
		// not present mips in data
		uint32_t GetMipLevelCount() const override;

		void Lock() override;
		void Unlock() override;

		Buffer GetWriteableBuffer() override;

		const std::string& GetPath() const override { return m_FilePath; }

		bool Loaded() const override { return m_Loaded; }

		uint64_t GetHash() const override { return m_Image->GetHash(); }

	private:
		Ref<Image2D> m_Image;
		TextureProperties m_Properties;
		uint32_t m_Width, m_Height;

		bool m_IsHDR = false;

		bool m_Locked = false;
		bool m_Loaded = false;

		std::string m_FilePath;
	};

	class OpenGLTextureCube : public TextureCube
	{
	public:
		OpenGLTextureCube(ImageFormat format, uint32_t width, uint32_t height, const void* data, TextureProperties properties);
		OpenGLTextureCube(const std::string& path, TextureProperties properties);
		~OpenGLTextureCube() override;

		void Bind(uint32_t slot = 0) const override;

		ImageFormat GetFormat() const override { return m_Format; }
		uint32_t GetWidth() const override { return m_Width; }
		uint32_t GetHeight() const override { return m_Height; }
		// This function currently returns the expected number of mips based on image size,
		// not present mips in data
		uint32_t GetMipLevelCount() const override;

		const std::string& GetPath() const override { return m_FilePath; }

		RendererID GetRendererID() const { return m_RendererID; }

		uint64_t GetHash() const override { return (uint64_t)m_RendererID; }

	private:
		RendererID m_RendererID;
		ImageFormat m_Format;
		uint32_t m_Width, m_Height;

		TextureProperties m_Properties;

		Buffer m_LocalStorage;

		std::string m_FilePath;
	};
}
