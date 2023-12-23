set_project("Hephaestus")

includes("../../../external/Glad")
includes("../../../external/GLFW")
includes("../../../external/imgui")
includes("../../../external/yaml-cpp")
includes("../../../external/Box2D")
add_repositories("glfw /external/GLFW", {rootdir = os.projectdir()})
add_requires("glfw")
if (is_mode("debug")) then
	add_requires("assimp >= 5.2.4")
else
	add_requires("assimp >= 5.2.4")
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

LibraryDir = {}
LibraryDir["mono"] = "$(projectdir)/external/mono/lib/Debug/mono-2.0-sgen.lib"

BuildProject({
	projectName = "Hephaestus",
	projectType = "static",
	macros = {"HEP_BUILD_DLL"},
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
	},
	packages = {"glfw"},
	debugLink = {},
	releaseLink = {},
	link = { "kernel32", "User32", "Gdi32", "Shell32", "Comdlg32", "opengl32.lib", LibraryDir.mono },
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
	packages = {"assimp"},
	debugLink = {},
	releaseLink = {},
	link = {"kernel32", "User32", "Gdi32", "Shell32"},
	afterBuildFunc = function (target)
		if is_plat("windows") then
			src_path = ""
			if (is_mode("debug")) then
				src_path = "$(projectdir)/external/mono/bin/Debug/mono-2.0-sgen.dll"
			else
				src_path = "$(projectdir)/external/mono/bin/Release/mono-2.0-sgen.dll"
			end
			os.cp(src_path, target:targetdir())
		end
	end,
	enableException = true,
	staticruntime = true,
	startproject = true,
	group = "Tools",
})