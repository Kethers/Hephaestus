#pragma once

#include "Hephaestus/Renderer/IndexBuffer.h"

#include "Hephaestus/Core/Buffer.h"

#include "VulkanAllocator.h"

namespace Hep
{
	class VulkanIndexBuffer : public IndexBuffer
	{
	public:
		VulkanIndexBuffer(uint32_t size);
		VulkanIndexBuffer(void* data, uint32_t size = 0);

		void SetData(void* buffer, uint32_t size, uint32_t offset = 0) override;
		void Bind() const override;

		uint32_t GetCount() const override { return m_Size / sizeof(uint32_t); }

		uint32_t GetSize() const override { return m_Size; }
		RendererID GetRendererID() const override;

		VkBuffer GetVulkanBuffer() { return m_VulkanBuffer; }

	private:
		uint32_t m_Size = 0;
		Buffer m_LocalData;

		VkBuffer m_VulkanBuffer;
		VkDeviceMemory m_DeviceMemory;
	};
}
