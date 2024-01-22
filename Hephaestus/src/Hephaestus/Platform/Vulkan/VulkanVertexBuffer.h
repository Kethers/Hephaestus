#pragma once

#include "Hephaestus/Renderer/VertexBuffer.h"

#include "Hephaestus/Core/Buffer.h"

#include "VulkanAllocator.h"

namespace Hep
{
	class VulkanVertexBuffer : public VertexBuffer
	{
	public:
		VulkanVertexBuffer(void* data, uint32_t size, VertexBufferUsage usage = VertexBufferUsage::Static);
		VulkanVertexBuffer(uint32_t size, VertexBufferUsage usage = VertexBufferUsage::Dynamic);

		~VulkanVertexBuffer() override {}

		void SetData(void* buffer, uint32_t size, uint32_t offset = 0) override {}
		void Bind() const override {}

		const VertexBufferLayout& GetLayout() const override { return {}; }
		void SetLayout(const VertexBufferLayout& layout) override {}

		unsigned int GetSize() const override { return m_Size; }
		RendererID GetRendererID() const override { return 0; }

		VkBuffer GetVulkanBuffer() { return m_VulkanBuffer; }

	private:
		uint32_t m_Size = 0;
		Buffer m_LocalData;

		VkBuffer m_VulkanBuffer;
		VkDeviceMemory m_DeviceMemory;
	};
}
