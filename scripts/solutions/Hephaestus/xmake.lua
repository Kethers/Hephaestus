set_project("Hephaestus")

includes("../../util/dependencies.lua")

BuildProject({
	projectName = "Hephaestus",
	projectType = "static",
	macros = {"HEP_BUILD_DLL", "PX_PHYSX_STATIC_LIB"},
	languages = {"clatest", "cxx20"},
	depends = {"Glad", "ImGui", "yaml-cpp", "Box2D"},
	files = {
		"$(projectdir)/Hephaestus/src/**.cpp", 
		"$(projectdir)/external/stb/**.cpp", 
		"$(projectdir)/external/FastNoise/**.cpp",
		"$(projectdir)/external/VulkanMemoryAllocator/**.cpp", 
	},
	headerfiles = {
		"$(projectdir)/Hephaestus/src/**.h", 
		"$(projectdir)/Hephaestus/src/**.hpp",
		"$(projectdir)/external/stb/**.h",
		"$(projectdir)/external/VulkanMemoryAllocator/**.h", 
	},
	pchHeader = "$(projectdir)/Hephaestus/src/heppch.h",
	includePaths = {
		"$(projectdir)/external", 
		"$(projectdir)/Hephaestus/src", 
		IncludeDir.Glad,
		IncludeDir.ImGui,
		IncludeDir.glm,
		IncludeDir.assimp,
		IncludeDir.stb,
		IncludeDir.entt,
		IncludeDir.FastNoise,
		IncludeDir.mono,
		IncludeDir["yaml-cpp"],
		IncludeDir.Box2D,
		IncludeDir.PhysX,
		IncludeDir.NvidiaAftermath,
	},
	packages = {"glfw", "vulkansdk"},
	debugLink = {
		Library.ShaderC_Debug,
		Library.SPIRV_Cross_Debug,
		Library.SPIRV_Cross_GLSL_Debug,
		Library.SPIRV_Tools_Debug,
	},
	releaseLink = {
		Library.ShaderC_Release, 
		Library.SPIRV_Cross_Release, 
		Library.SPIRV_Cross_GLSL_Release,
	},
	link = { "kernel32", "User32", "Gdi32", "Shell32", "Comdlg32", "opengl32.lib", 
		Library.mono,
		Library.PhysX,
		Library.PhysXCharacterKinematic,
		Library.PhysXCommon,
		Library.PhysXCooking,
		Library.PhysXExtensions,
		Library.PhysXFoundation,
		Library.PhysXPvd,
		Library.NvidiaAftermath,
	},
	cxflags = {},
	afterBuildFunc = nil,
	enableException = true,
	staticruntime = false,
	group = "Core",
})

BuildProject({
	projectName = "Hephaestus-ScriptCore",
	projectType = "shared",
	macros = {},
	languages = {"csharp"},
	depends = {},
	files = {"$(projectdir)/Hephaestus-ScriptCore/src/**.cs"},
	headerfiles = {},
	pchHeader = nil,
	includePaths = {},
	rundir = "$(projectdir)/Hephaestus-ScriptCore",
	packages = {},
	debugLink = {},
	releaseLink = {},
	link = {},
	afterBuildFunc = nil,
	enableException = true,
	staticruntime = false,
	group = "Core",
})

BuildProject({
	projectName = "Poseidon",
	projectType = "binary",
	macros = {},
	languages = {"clatest", "cxx20"},
	depends = {"Hephaestus"},
	files = {"$(projectdir)/Poseidon/src/**.cpp"},
	headerfiles = {"$(projectdir)/Poseidon/src/**.hpp", "$(projectdir)/Poseidon/src/**.h"},
	pchHeader = nil,
	includePaths = {
		"$(projectdir)/external", 
		"$(projectdir)/Hephaestus/src", 
		"$(projectdir)/Poseidon/src",
		IncludeDir.glm,
		IncludeDir.entt,
		IncludeDir.ImGui,
		IncludeDir.Glad,
	},
	rundir = "$(projectdir)/Poseidon",
	packages = {--[["assimp"]]},
	debugLink = {"$(projectdir)/external/assimp/bin/Debug/assimp-vc141-mtd.lib"},
	releaseLink = {"$(projectdir)/external/assimp/bin/Release/assimp-vc141-mt.lib"},
	link = {"kernel32", "User32", "Gdi32", "Shell32"},
	afterBuildFunc = function (target)
		if is_plat("windows") then
			os.cp("$(projectdir)/external/NvidiaAftermath/lib/x64/GFSDK_Aftermath_Lib.x64.dll", target:targetdir())
			if (is_mode("debug")) then
				-- TODO: Temp, try other way
				os.cp(path.join(os.getenv("VULKAN_SDK"), "Bin", "shaderc_sharedd.dll"), target:targetdir())
				os.cp("$(projectdir)/external/assimp/bin/Debug/assimp-vc141-mtd.dll", target:targetdir())
				os.cp("$(projectdir)/external/mono/bin/Debug/mono-2.0-sgen.dll", target:targetdir())
			else
				os.cp("$(projectdir)/external/assimp/bin/Release/assimp-vc141-mt.dll", target:targetdir())
				os.cp("$(projectdir)/external/mono/bin/Release/mono-2.0-sgen.dll", target:targetdir())
			end
		end
	end,
	enableException = true,
	staticruntime = false,
	startproject = true,
	group = "Tools",
})


--[[BuildProject({
	projectName = "Sandbox",
	projectType = "binary",
	macros = {},
	languages = {"clatest", "cxx20"},
	depends = {"Hephaestus"},
	files = {"Sandbox/src/**.cpp"},
	headerfiles = {"Sandbox/src/**.hpp", "Sandbox/src/**.h"},
	pchHeader = nil,
	includePaths = {"external", "Hephaestus/src", "Sandbox/src",
		IncludeDir.glm,
		IncludeDir.entt,
		IncludeDir.VulkanSDK,
	},
	rundir = "$(projectdir)/Sandbox",
	packages = {"assimp"},
	debugLink = {},
	releaseLink = {},
	link = {"kernel32", "User32", "Gdi32", "Shell32"},
	afterBuildFunc = nil,
	enableException = true,
	staticruntime = true,
	startproject = false,
})--]]