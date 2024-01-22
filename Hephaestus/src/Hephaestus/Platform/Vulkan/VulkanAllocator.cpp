#include "heppch.h"
#include "VulkanAllocator.h"

#include "VulkanContext.h"

namespace Hep
{
	namespace Utils
	{
		std::string BytesToString(uint64_t bytes)
		{
			static constexpr int gb = 1024 * 1024 * 1024;
			static constexpr int mb = 1024 * 1024;
			static constexpr int kb = 1024;

			std::string res;

			if (bytes > gb)
				res = std::format("{:.2f} GB", (float)bytes / gb);
			else if (bytes > mb)
				res = std::format("{:.2f} MB", (float)bytes / mb);
			else if (bytes > kb)
				res = std::format("{:.2f} KB", (float)bytes / kb);
			else
				res = std::format("{:.2f} Bytes", (float)bytes);

			return res;
		}
	}

	struct VulkanAllocatorData
	{
		VmaAllocator Allocator;
		uint64_t TotalAllocatedBytes = 0;
	};

	static VulkanAllocatorData* s_Data = nullptr;

	VulkanAllocator::VulkanAllocator(const std::string& tag)
		: m_Tag(tag)
	{}

	VulkanAllocator::~VulkanAllocator() = default;

#if 0
	void VulkanAllocator::Allocate(VkMemoryRequirements requirements, VkDeviceMemory* dest, VkMemoryPropertyFlags flags)
	{
		HEP_CORE_ASSERT(m_Device);

		// TODO: Tracking
		HEP_CORE_TRACE("VulkanAllocator ({0}): allocating {1}", m_Tag, Utils::BytesToString(requirements.size));

		{
			static uint64_t totalAllocatedBytes = 0;
			totalAllocatedBytes += requirements.size;
			HEP_CORE_TRACE("VulkanAllocator ({0}): total allocated since start is {1}", m_Tag, Utils::BytesToString(totalAllocatedBytes));
		}

		VkMemoryAllocateInfo memAlloc{};
		memAlloc.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		memAlloc.allocationSize = requirements.size;
		memAlloc.memoryTypeIndex = m_Device->GetPhysicalDevice()->GetMemoryTypeIndex(requirements.memoryTypeBits, flags);
		VK_CHECK_RESULT(vkAllocateMemory(m_Device->GetVulkanDevice(), &memAlloc, nullptr, dest));
	}
#endif

	VmaAllocation VulkanAllocator::AllocateBuffer(VkBufferCreateInfo bufferCreateInfo, VmaMemoryUsage usage, VkBuffer& outBuffer)
	{
		VmaAllocationCreateInfo allocCreateInfo{};
		allocCreateInfo.usage = usage;

		VmaAllocation allocation;
		VmaAllocationInfo allocInfo;
		vmaCreateBuffer(s_Data->Allocator, &bufferCreateInfo, &allocCreateInfo, &outBuffer, &allocation, &allocInfo);

		// TODO: Tracking
		// vmaGetAllocationInfo(s_Data->Allocator, allocation, &allocInfo);
		HEP_CORE_TRACE("VulkanAllocator ({0}): allocating buffer; size = {1}", m_Tag, Utils::BytesToString(allocInfo.size));

		{
			s_Data->TotalAllocatedBytes += allocInfo.size;
			HEP_CORE_TRACE("VulkanAllocator ({0}): total allocated since start is {1}", m_Tag,
				Utils::BytesToString(s_Data->TotalAllocatedBytes));
		}

		return allocation;
	}

	VmaAllocation VulkanAllocator::AllocateImage(VkImageCreateInfo imageCreateInfo, VmaMemoryUsage usage, VkImage& outImage)
	{
		VmaAllocationCreateInfo allocCreateInfo = {};
		allocCreateInfo.usage = usage;

		VmaAllocation allocation;
		VmaAllocationInfo allocInfo;
		vmaCreateImage(s_Data->Allocator, &imageCreateInfo, &allocCreateInfo, &outImage, &allocation, &allocInfo);

		// TODO: Tracking
		// vmaGetAllocationInfo(s_Data->Allocator, allocation, &allocInfo);
		HEP_CORE_TRACE("VulkanAllocator ({0}): allocating image; size = {1}", m_Tag, Utils::BytesToString(allocInfo.size));

		{
			s_Data->TotalAllocatedBytes += allocInfo.size;
			HEP_CORE_TRACE("VulkanAllocator ({0}): total allocated since start is {1}", m_Tag,
				Utils::BytesToString(s_Data->TotalAllocatedBytes));
		}
		return allocation;
	}

	void VulkanAllocator::Free(VmaAllocation allocation)
	{
		vmaFreeMemory(s_Data->Allocator, allocation);
	}

	void VulkanAllocator::DestroyImage(VkImage image, VmaAllocation allocation)
	{
		HEP_CORE_ASSERT(image);
		HEP_CORE_ASSERT(allocation);
		vmaDestroyImage(s_Data->Allocator, image, allocation);
	}

	void VulkanAllocator::DestroyBuffer(VkBuffer buffer, VmaAllocation allocation)
	{
		HEP_CORE_ASSERT(buffer);
		HEP_CORE_ASSERT(allocation);
		vmaDestroyBuffer(s_Data->Allocator, buffer, allocation);
	}

	void VulkanAllocator::UnmapMemory(VmaAllocation allocation)
	{
		vmaUnmapMemory(s_Data->Allocator, allocation);
	}

	void VulkanAllocator::DumpStats()
	{
		VmaTotalStatistics stats;
		vmaCalculateStatistics(s_Data->Allocator, &stats);

		uint64_t usedMemory = stats.memoryHeap[0].statistics.allocationBytes;
		uint64_t totalMemory = stats.memoryHeap[0].statistics.blockBytes;
	}

	GPUMemoryStats VulkanAllocator::GetStats()
	{
		VmaTotalStatistics stats;
		vmaCalculateStatistics(s_Data->Allocator, &stats);

		uint64_t usedMemory = stats.total.statistics.allocationBytes;
		uint64_t totalMemory = stats.total.statistics.blockBytes;

		return { usedMemory, totalMemory - usedMemory };
	}

	void VulkanAllocator::Init(Ref<VulkanDevice> device)
	{
		s_Data = new VulkanAllocatorData();

		// Initialize VulkanMemoryAllocator
		VmaAllocatorCreateInfo allocatorInfo = {};
		allocatorInfo.vulkanApiVersion = VK_API_VERSION_1_3;
		allocatorInfo.physicalDevice = device->GetPhysicalDevice()->GetVulkanPhysicalDevice();
		allocatorInfo.device = device->GetVulkanDevice();
		allocatorInfo.instance = VulkanContext::GetInstance();

		vmaCreateAllocator(&allocatorInfo, &s_Data->Allocator);
	}

	void VulkanAllocator::Shutdown()
	{
		vmaDestroyAllocator(s_Data->Allocator);

		delete s_Data;
		s_Data = nullptr;
	}

	VmaAllocator& VulkanAllocator::GetVMAAllocator()
	{
		return s_Data->Allocator;
	}
}
