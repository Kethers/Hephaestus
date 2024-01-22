#pragma once

#include "Vulkan.h"

namespace Hep::Utils
{
	struct VulkanCheckpointData
	{
		char Data[64];
	};

	void SetVulkanCheckpoint(VkCommandBuffer commandBuffer, const std::string& data);
}
