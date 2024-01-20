#pragma once

#include "Hephaestus/Renderer/Texture.h"

#include "Vulkan.h"

#include "VulkanImage.h"

namespace Hep
{
	class VulkanTexture2D : public Texture2D
	{
	public:
		VulkanTexture2D(const std::string& path, bool srgb = false);
		VulkanTexture2D(ImageFormat format, uint32_t width, uint32_t height, const void* data, TextureWrap wrap = TextureWrap::Clamp);
		~VulkanTexture2D() override;

		void Invalidate();

		ImageFormat GetFormat() const override { return m_Format; }
		uint32_t GetWidth() const override { return m_Width; }
		uint32_t GetHeight() const override { return m_Height; }

		void Bind(uint32_t slot = 0) const override;

		Ref<Image2D> GetImage() const override { return m_Image; }
		const VkDescriptorImageInfo& GetVulkanDescriptorInfo() const { return m_Image.As<VulkanImage2D>()->GetDescriptor(); }

		void Lock() override;
		void Unlock() override;

		Buffer GetWriteableBuffer() override;
		bool Loaded() const override;
		const std::string& GetPath() const override;
		uint32_t GetMipLevelCount() const override;

		void GenerateMips();

		uint64_t GetHash() const override { return (uint64_t)m_Image; }

	private:
		std::string m_Path;
		uint32_t m_Width;
		uint32_t m_Height;

		Buffer m_ImageData;

		Ref<Image2D> m_Image;

		ImageFormat m_Format = ImageFormat::None;
	};

	class VulkanTextureCube : public TextureCube
	{
	public:
		VulkanTextureCube(ImageFormat format, uint32_t width, uint32_t height, const void* data = nullptr);
		VulkanTextureCube(const std::string& path);
		~VulkanTextureCube() override;

		const std::string& GetPath() const override { return ""; }

		void Bind(uint32_t slot = 0) const override {}

		ImageFormat GetFormat() const override { return m_Format; }

		uint32_t GetWidth() const override { return m_Width; }
		uint32_t GetHeight() const override { return m_Height; }
		uint32_t GetMipLevelCount() const override;

		uint64_t GetHash() const override { return (uint64_t)m_Image; }

		const VkDescriptorImageInfo& GetVulkanDescriptorInfo() const { return m_DescriptorImageInfo; }
		VkImageView CreateImageViewSingleMip(uint32_t mip);

		void GenerateMips(bool readonly = false);

	private:
		void Invalidate();

	private:
		ImageFormat m_Format = ImageFormat::None;
		uint32_t m_Width = 0, m_Height = 0;

		bool m_MipsGenerated = false;

		Buffer m_LocalStorage;
		VkDeviceMemory m_DeviceMemory;
		VkImage m_Image;
		VkDescriptorImageInfo m_DescriptorImageInfo = {};
	};
}
