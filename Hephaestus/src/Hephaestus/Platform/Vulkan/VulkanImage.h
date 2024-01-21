﻿#pragma once

#include "Hephaestus/Renderer/Image.h"

#include "vulkan/vulkan.h"
#include "VulkanMemoryAllocator/vk_mem_alloc.h"

namespace Hep
{
	struct VulkanImageInfo
	{
		VkImage Image;
		VkImageView ImageView;
		VkSampler Sampler;
		VmaAllocation MemoryAlloc = nullptr;
	};

	class VulkanImage2D : public Image2D
	{
	public:
		VulkanImage2D(ImageFormat format, uint32_t width, uint32_t height);
		~VulkanImage2D() override;

		void Invalidate() override;
		void Release() override;

		uint32_t GetWidth() const override { return m_Width; }
		uint32_t GetHeight() const override { return m_Height; }

		ImageFormat GetFormat() const override { return m_Format; }

		VulkanImageInfo& GetImageInfo() { return m_Info; }
		const VulkanImageInfo& GetImageInfo() const { return m_Info; }

		const VkDescriptorImageInfo& GetDescriptor() { return m_DescriptorImageInfo; }

		Buffer GetBuffer() const override { return m_ImageData; }
		Buffer& GetBuffer() override { return m_ImageData; }

		uint64_t GetHash() const override { return (uint64_t)m_Info.Image; }

		void UpdateDescriptor();

	private:
		ImageFormat m_Format;
		uint32_t m_Width = 0, m_Height = 0;

		Buffer m_ImageData;

		VulkanImageInfo m_Info;
		VkDescriptorImageInfo m_DescriptorImageInfo = {};
	};

	namespace Utils
	{
		inline VkFormat VulkanImageFormat(ImageFormat format)
		{
			switch (format)
			{
				case ImageFormat::RGBA: return VK_FORMAT_R8G8B8A8_UNORM;
				case ImageFormat::RGBA32F: return VK_FORMAT_R32G32B32A32_SFLOAT;
			}
			HEP_CORE_ASSERT(false);
			return VK_FORMAT_UNDEFINED;
		}
	}
}
