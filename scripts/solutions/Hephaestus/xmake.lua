set_project("Hephaestus")

includes("../../util/dependencies.lua")
includes("../../../external/Glad")
includes("../../../external/GLFW")
includes("../../../external/imgui")
includes("../../../external/yaml-cpp")
includes("../../../external/Box2D")
add_repositories("glfw /external/GLFW", {rootdir = os.projectdir()})
add_requires("glfw")
-- TEMP: bug on 5.2.4 MTd, disable for, emm... now?
-- if is_mode("debug") then
-- 	add_requires("assimp >= 5.2.4", {configs = {debug = true, vs_runtime = "MTd"}} )
-- else
-- 	add_requires("assimp >= 5.2.4", {configs = {debug = false, vs_runtime = "MT"}} )
-- end

BuildProject({
	projectName = "Hephaestus",
	projectType = "static",
	macros = {"HEP_BUILD_DLL", "PX_PHYSX_STATIC_LIB"},
	languages = {"clatest", "cxx20"},
	depends = {"Glad", "ImGui", "yaml-cpp", "Box2D"},
	files = {
		"$(projectdir)/Hephaestus/src/**.cpp", 
		"$(projectdir)/external/stb/**.cpp", 
		"$(projectdir)/external/FastNoise/**.cpp"
	},
	headerfiles = {
		"$(projectdir)/Hephaestus/src/**.h", 
		"$(projectdir)/Hephaestus/src/**.hpp",
		"$(projectdir)/external/stb/**.h",
	},
	pchHeader = "$(projectdir)/Hephaestus/src/heppch.h",
	includePaths = {
		"$(projectdir)/external", 
		"$(projectdir)/Hephaestus/src", 
		IncludeDir.GLFW, 
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
		IncludeDir.VulkanSDK,
	},
	packages = {"glfw"},
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
		Library.Vulkan,
		-- Library.VulkanUtils,
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
		IncludeDir.VulkanSDK,
		IncludeDir.Glad,
	},
	rundir = "$(projectdir)/Poseidon",
	packages = {--[["assimp"]]},
	debugLink = {"$(projectdir)/external/assimp/bin/Debug/assimp-vc141-mtd.lib"},
	releaseLink = {"$(projectdir)/external/assimp/bin/Release/assimp-vc141-mt.lib"},
	link = {"kernel32", "User32", "Gdi32", "Shell32"},
	afterBuildFunc = function (target)
		if is_plat("windows") then
			if (is_mode("debug")) then
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