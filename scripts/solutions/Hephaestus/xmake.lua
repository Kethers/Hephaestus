set_project("Hephaestus")

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

LibraryDir = {}
LibraryDir["mono"] 							= "$(projectdir)/external/mono/lib/Debug/mono-2.0-sgen.lib"

LibraryDir["PhysX"] 						= "$(projectdir)/external/PhysX/lib/$(mode)/PhysX_static_64.lib"
LibraryDir["PhysXCharacterKinematic"] 		= "$(projectdir)/external/PhysX/lib/$(mode)/PhysXCharacterKinematic_static_64.lib"
LibraryDir["PhysXCommon"] 					= "$(projectdir)/external/PhysX/lib/$(mode)/PhysXCommon_static_64.lib"
LibraryDir["PhysXCooking"] 					= "$(projectdir)/external/PhysX/lib/$(mode)/PhysXCooking_static_64.lib"
LibraryDir["PhysXExtensions"] 				= "$(projectdir)/external/PhysX/lib/$(mode)/PhysXExtensions_static_64.lib"
LibraryDir["PhysXFoundation"] 				= "$(projectdir)/external/PhysX/lib/$(mode)/PhysXFoundation_static_64.lib"
LibraryDir["PhysXPvd"] 						= "$(projectdir)/external/PhysX/lib/$(mode)/PhysXPvdSDK_static_64.lib"


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
	},
	packages = {"glfw"},
	debugLink = {},
	releaseLink = {},
	link = { "kernel32", "User32", "Gdi32", "Shell32", "Comdlg32", "opengl32.lib", 
		LibraryDir.mono,
		LibraryDir.PhysX,
		LibraryDir.PhysXCharacterKinematic,
		LibraryDir.PhysXCommon,
		LibraryDir.PhysXCooking,
		LibraryDir.PhysXExtensions,
		LibraryDir.PhysXFoundation,
		LibraryDir.PhysXPvd,
	},
	cxflags = {},
	afterBuildFunc = nil,
	enableException = true,
	staticruntime = true,
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
	},
	rundir = "$(projectdir)/Poseidon",
	packages = {--[["assimp"]]},
	debugLink = {"$(projectdir)/external/assimp/bin/Debug/assimp-vc143-mtd.lib"},
	releaseLink = {"$(projectdir)/external/assimp/bin/Release/assimp-vc143-mt.lib"},
	link = {"kernel32", "User32", "Gdi32", "Shell32"},
	afterBuildFunc = function (target)
		if is_plat("windows") then
			if (is_mode("debug")) then
				os.cp("$(projectdir)/external/assimp/bin/Debug/assimp-vc143-mtd.dll", target:targetdir())
				os.cp("$(projectdir)/external/mono/bin/Debug/mono-2.0-sgen.dll", target:targetdir())
			else
				os.cp("$(projectdir)/external/assimp/bin/Release/assimp-vc143-mt.dll", target:targetdir())
				os.cp("$(projectdir)/external/mono/bin/Release/mono-2.0-sgen.dll", target:targetdir())
			end
		end
	end,
	enableException = true,
	staticruntime = true,
	startproject = true,
	group = "Tools",
})