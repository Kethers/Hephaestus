-- Hephaestus Dependencies

includes("../../external/GLFW/xmake.lua")
includes("../../external/yaml-cpp/xmake.lua")
includes("../../external/Glad/xmake.lua")
includes("../../external/imgui/xmake.lua")
includes("../../external/Box2D/xmake.lua")

add_repositories("glfw /external/GLFW", {rootdir = os.projectdir()})
add_requires("glfw")
-- TEMP: bug on 5.2.4 MTd, disable for, emm... now?
-- if is_mode("debug") then
-- 	add_requires("assimp >= 5.2.4", {configs = {debug = true, vs_runtime = "MTd"}} )
-- else
-- 	add_requires("assimp >= 5.2.4", {configs = {debug = false, vs_runtime = "MT"}} )
-- end


add_requires("vulkansdk")
VULKAN_SDK = os.getenv("VULKAN_SDK")

if VULKAN_SDK == nil then
	os.raise("Can't find VULKAN_SDK, please make sure Vulkan SDK is installed!")
end

IncludeDir = {}
IncludeDir["GLFW"] 		= "$(projectdir)/external/GLFW/include"
IncludeDir["Glad"] 		= "$(projectdir)/external/Glad/include"
IncludeDir["ImGui"] 	= "$(projectdir)/external/imgui"
IncludeDir["glm"] 		= "$(projectdir)/external/glm"
IncludeDir["assimp"] 	= "$(projectdir)/external/assimp/include"
IncludeDir['stb'] 		= "$(projectdir)/external/stb"
IncludeDir["entt"] 		= "$(projectdir)/external/entt/include"
IncludeDir["FastNoise"] = "$(projectdir)/external/FastNoise"
IncludeDir["mono"] 		= "$(projectdir)/external/mono/include"
IncludeDir["yaml-cpp"] 	= "$(projectdir)/external/yaml-cpp/include"
IncludeDir["Box2D"] 	= "$(projectdir)/external/Box2D/include"
IncludeDir["PhysX"]		= "$(projectdir)/external/PhysX/include"
IncludeDir["VulkanSDK"] = path.join(VULKAN_SDK, "Include")
IncludeDir["NvidiaAftermath"] = "$(projectdir)/external/NvidiaAftermath/include"


LibraryDir = {}

LibraryDir["PhysX"] = "$(projectdir)/external/PhysX/lib/$(mode)"
LibraryDir["VulkanSDK"] = path.join(VULKAN_SDK, "Lib")
LibraryDir["NvidiaAftermath"] = "$(projectdir)/external/NvidiaAftermath/lib/x64"


Library = {}
Library["mono"] 					= "$(projectdir)/external/mono/lib/Debug/mono-2.0-sgen.lib"

Library["PhysX"] 					= path.join(LibraryDir.PhysX, "PhysX_static_64.lib")
Library["PhysXCharacterKinematic"] 	= path.join(LibraryDir.PhysX, "PhysXCharacterKinematic_static_64.lib")
Library["PhysXCommon"] 				= path.join(LibraryDir.PhysX, "PhysXCommon_static_64.lib")
Library["PhysXCooking"] 			= path.join(LibraryDir.PhysX, "PhysXCooking_static_64.lib")
Library["PhysXExtensions"] 			= path.join(LibraryDir.PhysX, "PhysXExtensions_static_64.lib")
Library["PhysXFoundation"] 			= path.join(LibraryDir.PhysX, "PhysXFoundation_static_64.lib")
Library["PhysXPvd"] 				= path.join(LibraryDir.PhysX, "PhysXPvdSDK_static_64.lib")
Library["Vulkan"] 					= path.join(LibraryDir.VulkanSDK, "vulkan-1.lib")
Library["NvidiaAftermath"] 			= path.join(LibraryDir.NvidiaAftermath, "GFSDK_Aftermath_Lib.x64.lib")

Library["ShaderC_Debug"] 			= path.join(LibraryDir.VulkanSDK, "shaderc_sharedd.lib")
Library["SPIRV_Cross_Debug"] 		= path.join(LibraryDir.VulkanSDK, "spirv-cross-cored.lib")
Library["SPIRV_Cross_GLSL_Debug"] 	= path.join(LibraryDir.VulkanSDK, "spirv-cross-glsld.lib")
Library["SPIRV_Tools_Debug"] 		= path.join(LibraryDir.VulkanSDK, "SPIRV-Toolsd.lib")

Library["ShaderC_Release"] 			= path.join(LibraryDir.VulkanSDK, "shaderc_shared.lib")
Library["SPIRV_Cross_Release"] 		= path.join(LibraryDir.VulkanSDK, "spirv-cross-core.lib")
Library["SPIRV_Cross_GLSL_Release"] = path.join(LibraryDir.VulkanSDK, "spirv-cross-glsl.lib")