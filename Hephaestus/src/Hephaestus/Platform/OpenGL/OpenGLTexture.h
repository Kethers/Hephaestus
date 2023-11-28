#pragma once

#include "Hephaestus//Renderer/RendererAPI.h"
#include "Hephaestus/Renderer/Texture.h"

namespace Hep
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(TextureFormat format, unsigned int width, unsigned int height);
		OpenGLTexture2D(const std::string& path, bool srgb);
		~OpenGLTexture2D() override;

		void Bind(unsigned int slot = 0) const override;

		TextureFormat GetFormat() const override { return m_Format; }
		unsigned int GetWidth() const override { return m_Width; }
		unsigned int GetHeight() const override { return m_Height; }

		const std::string& GetPath() const override { return m_FilePath; }

		RendererID GetRendererID() const override { return m_RendererID; }

	private:
		RendererID m_RendererID;
		TextureFormat m_Format;
		unsigned int m_Width, m_Height;

		unsigned char* m_ImageData;

		std::string m_FilePath;
	};

	class OpenGLTextureCube : public TextureCube
	{
	public:
		OpenGLTextureCube(const std::string& path);
		~OpenGLTextureCube() override;

		void Bind(unsigned int slot = 0) const override;

		TextureFormat GetFormat() const override { return m_Format; }
		unsigned int GetWidth() const override { return m_Width; }
		unsigned int GetHeight() const override { return m_Height; }

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
