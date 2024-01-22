﻿#include "heppch.h"
#include "VulkanContext.h"
#include "Vulkan.h"

#include <GLFW/glfw3.h>

namespace Hep
{
#ifdef HEP_DEBUG
	static constexpr bool s_Validation = true;
#else
	static constexpr bool s_Validation = false;
#endif

	static VKAPI_ATTR VkBool32 VKAPI_CALL VulkanDebugReportCallback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objectType,
		uint64_t object, size_t location, int32_t messageCode, const char* pLayerPrefix, const char* pMessage, void* pUserData)
	{
		(void)flags;
		(void)object;
		(void)location;
		(void)messageCode;
		(void)pUserData;
		(void)pLayerPrefix; // Unused arguments
		HEP_CORE_WARN("VulkanDebugCallback:\n  Object Type: {0}\n  Message: {1}", objectType, pMessage);
		return VK_FALSE;
	}

	VulkanContext::VulkanContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{}

	VulkanContext::~VulkanContext()
	{
		m_SwapChain.Cleanup();
		m_Device->Destroy();

		vkDestroyInstance(s_VulkanInstance, nullptr);
		s_VulkanInstance = nullptr;
	}

	void VulkanContext::Create()
	{
		HEP_CORE_INFO("VulkanContext::Create");

		HEP_CORE_ASSERT(glfwVulkanSupported(), "GLFW must support Vulkan!");

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Application Info
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		VkApplicationInfo appInfo{};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "Hephaestus";
		appInfo.pEngineName = "Hephaestus";
		appInfo.apiVersion = VK_API_VERSION_1_3;

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Extensions and Validation
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define VK_KHR_WIN32_SURFACE_EXTENSION_NAME "VK_KHR_win32_surface"
		std::vector<const char*> instanceExtensions = { VK_KHR_SURFACE_EXTENSION_NAME, VK_KHR_WIN32_SURFACE_EXTENSION_NAME };
		if constexpr (s_Validation)
		{
			instanceExtensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
			instanceExtensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
			instanceExtensions.push_back(VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME);
		}

		VkInstanceCreateInfo instanceCreateInfo{};
		instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		instanceCreateInfo.pNext = nullptr;
		instanceCreateInfo.pApplicationInfo = &appInfo;
		instanceCreateInfo.enabledExtensionCount = (uint32_t)instanceExtensions.size();
		instanceCreateInfo.ppEnabledExtensionNames = instanceExtensions.data();

		// TODO: Extrace all validation into separate class
		if constexpr (s_Validation)
		{
			const char* validationLayerName = "VK_LAYER_KHRONOS_validation";
			// Check if this layer is available at instance level
			uint32_t instanceLayerCount;
			vkEnumerateInstanceLayerProperties(&instanceLayerCount, nullptr);
			std::vector<VkLayerProperties> instanceLayerProperties(instanceLayerCount);
			vkEnumerateInstanceLayerProperties(&instanceLayerCount, instanceLayerProperties.data());
			bool validationLayerPresent = false;
			HEP_CORE_TRACE("Vulkan Instance Layer:");
			for (const auto& layer : instanceLayerProperties)
			{
				HEP_CORE_TRACE("  {0}", layer.layerName);
				if (strcmp(layer.layerName, validationLayerName) == 0)
				{
					validationLayerPresent = true;
					break;
				}
			}
			if (validationLayerPresent)
			{
				instanceCreateInfo.ppEnabledLayerNames = &validationLayerName;
				instanceCreateInfo.enabledLayerCount = 1;
			}
			else
			{
				HEP_CORE_ERROR("Validation layer VK_LAYER_LUNARG_standard_validation not present, validation is disabled");
			}
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Instance and Surface Creation
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		VK_CHECK_RESULT(vkCreateInstance(&instanceCreateInfo, nullptr, &s_VulkanInstance));

		if constexpr (s_Validation)
		{
			auto vkCreateDebugReportCallbackEXT = (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(s_VulkanInstance,
				"vkCreateDebugReportCallbackEXT");
			HEP_CORE_ASSERT(vkCreateDebugReportCallbackEXT != NULL, "")
			VkDebugReportCallbackCreateInfoEXT debugReportCI{};
			debugReportCI.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
			debugReportCI.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT |
				VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT;
			debugReportCI.pfnCallback = VulkanDebugReportCallback;
			debugReportCI.pUserData = nullptr;
			VK_CHECK_RESULT(vkCreateDebugReportCallbackEXT(s_VulkanInstance, &debugReportCI, nullptr, &m_DebugReportCallback));
		}

		m_PhysicalDevice = VulkanPhysicalDevice::Select();

		VkPhysicalDeviceFeatures enabledFeatures{};
		memset(&enabledFeatures, 0, sizeof(VkPhysicalDeviceFeatures));
		enabledFeatures.samplerAnisotropy = true;
		enabledFeatures.robustBufferAccess = true;
		m_Device = Ref<VulkanDevice>::Create(m_PhysicalDevice, enabledFeatures);

		VulkanAllocator::Init(m_Device);

		m_SwapChain.Init(s_VulkanInstance, m_Device);
		m_SwapChain.InitSurface(m_WindowHandle);

		uint32_t width = 1280, height = 720;
		m_SwapChain.Create(&width, &height);

		// Pipeline Cache
		VkPipelineCacheCreateInfo pipelineCacheCreateInfo{};
		pipelineCacheCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO;
		VK_CHECK_RESULT(vkCreatePipelineCache(m_Device->GetVulkanDevice(), &pipelineCacheCreateInfo, nullptr, &m_PipelineCache));
	}

	void VulkanContext::OnResize(uint32_t width, uint32_t height)
	{
		m_SwapChain.OnResize(width, height);
	}

	void VulkanContext::BeginFrame()
	{
		m_SwapChain.BeginFrame();
	}

	void VulkanContext::SwapBuffers()
	{
		m_SwapChain.Present();
	}
}