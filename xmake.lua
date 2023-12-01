set_project("Hephaestus")

set_xmakever("2.8.5")

add_rules("mode.debug", "mode.release")
add_rules("plugin.vsxmake.autoupdate")

set_allowedarchs("x64")
set_allowedplats("windows")
set_allowedmodes("debug", "release", "dist")

if is_os("windows") then
	add_defines("HEP_PLATFORM_WINDOWS")
end

if is_mode("debug") then
	add_defines("HEP_DEBUG")
elseif is_mode("release") then
	add_defines("HEP_RELEASE")
elseif is_mode("dist") then
	add_defines("HEP_DIST", "NDEBUG")
	set_optimize("fastest")
	set_symbols("hidden")
end

function Execute(map, func)
	if map ~= nil then
		for i, v in ipairs(map) do
			func(v)
		end
	end
end

function SetException(config)
	enableException = config.enableException
	if (enableException ~= nil) and (enableException) then
		add_cxflags("/EHsc", {
			force = true
		})
	end
end

function BuildProject(config)
	target(config.projectName)
	afterBuildFunc = config.afterBuildFunc
	if afterBuildFunc ~= nil then
		after_build(afterBuildFunc)
	end

	set_targetdir("$(buildir)/bin/$(mode)-$(plat)-$(arch)/" .. config.projectName)
	-- set_objectdir("$(buildir)/bin-int/$(mode)-$(plat)-$(arch)/" .. config.projectName)
	projectType = config.projectType
	if projectType ~= nil then
		set_kind(projectType)
		if projectType == "binary" then
			startProj = config.startproject
			if startProj ~= nil and startProj then
				set_default(true)
			else
				set_default(false)
			end
		end
	end

	pchHeader = config.pchHeader
	if pchHeader ~= nil then
		set_pcxxheader(pchHeader)
	end

	runDir = config.rundir
	if (runDir) ~= nil then
		set_rundir(runDir)
	end

	Execute(config.packages, add_packages)
	Execute(config.languages, set_languages)
	Execute(config.macros, add_defines)
	Execute(config.files, add_files)
	Execute(config.includePaths, add_includedirs)
	Execute(config.headerfiles, add_headerfiles)
	Execute(config.depends, add_deps)
	Execute(config.link, add_links)
	Execute(config.cxflags, add_cxflags)

	if is_mode("release") then
		Execute(config.releaseLink, add_links)
		set_optimize("fastest")
		if is_plat("windows") then
			if config.staticruntime ~= nil and config.staticruntime then
				set_runtimes("MT");
			else
				set_runtimes("MD")
			end
				
		-- 	add_cxflags("/Zi", "/W0", "/MP", "/Ob2", "/Oi", "/Ot", "/Oy", "/GT", "/GF", "/GS-", "/Gy", "/arch:AVX2",
		-- 		"/fp:precise", "/Gr", "/TP", {
		-- 			force = true
		-- 		})
			SetException(config)
		end
	else
		Execute(config.debugLink, add_links)
		set_optimize("none")
		if is_plat("windows") then
			if config.staticruntime ~= nil and config.staticruntime then
				set_runtimes("MT");
			else
				set_runtimes("MD")
			end
		-- 	add_cxflags("/Zi", "/W0", "/MP", "/Ob0", "/Oy-", "/GF", "/GS", "/arch:AVX2", "/fp:precise", "/Gr", "/TP", {
		-- 		force = true
		-- 	})
			SetException(config)
		end
	end
end

-- function copyFunc(target)
--     if is_plat("windows") then
--         build_path = ""
--         src_path = ""
--         if is_mode("release") then
--             src_path = "third_party/binary/release/"
--             build_path = "$(buildir)/windows/x64/release/"
--         else
--             src_path = "third_party/binary/debug/"
--             build_path = "$(buildir)/windows/x64/debug/"
--         end
--         os.cp(src_path .. "*.*", build_path)
--         os.cp("glfw/dll/glfw3.dll", build_path .. "glfw3.dll")
--     end
-- end

includes("external/Glad")
includes("external/GLFW")
includes("external/imgui")
add_repositories("glfw external/GLFW", {rootdir = os.scriptdir()})
add_requires("glfw")
if (is_mode("debug")) then
	add_requires("assimp >= 5.2.4")
else
	add_requires("assimp >= 5.2.4")
end

IncludeDir = {}
IncludeDir["GLFW"] = "external/GLFW/include"
IncludeDir["Glad"] = "external/Glad/include"
IncludeDir["ImGui"] = "external/imgui"
IncludeDir["glm"] = "external/glm"
IncludeDir["assimp"] = "external/assimp/include"
IncludeDir['stb'] = "external/stb"

BuildProject({
	projectName = "Hephaestus",
	projectType = "static",
	macros = {"HEP_BUILD_DLL"},
	languages = {"clatest", "cxx20"},
	depends = {"Glad", "ImGui"},
	files = {"Hephaestus/src/**.cpp", "external/stb/**.cpp"},
	headerfiles = {
		"Hephaestus/src/**.h", 
		"Hephaestus/src/**.hpp",
		"external/stb/**.h",
	},
	pchHeader = "Hephaestus/src/heppch.h",
	includePaths = {"external", "Hephaestus/src", 
		IncludeDir.GLFW, 
		IncludeDir.Glad,
		IncludeDir.ImGui,
		IncludeDir.glm,
		IncludeDir.assimp,
		IncludeDir.stb,
	},
	packages = {"glfw"},
	debugLink = {},
	releaseLink = {},
	link = {"kernel32", "User32", "Gdi32", "Shell32", "Comdlg32", "opengl32.lib"},
	afterBuildFunc = nil,
	enableException = true,
	staticruntime = true,
})

BuildProject({
	projectName = "Poseidon",
	projectType = "binary",
	macros = {},
	languages = {"clatest", "cxx20"},
	depends = {"Hephaestus"},
	files = {"Poseidon/src/**.cpp"},
	headerfiles = {"Poseidon/src/**.hpp", "Poseidon/src/**.h"},
	pchHeader = nil,
	includePaths = {"external", "Hephaestus/src", "Poseidon/src",
		IncludeDir.glm,
	},
	rundir = "$(projectdir)/Poseidon",
	packages = {"assimp"},
	debugLink = {},
	releaseLink = {},
	link = {"kernel32", "User32", "Gdi32", "Shell32"},
	afterBuildFunc = nil,
	enableException = true,
	staticruntime = true,
	startproject = true,
})


BuildProject({
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
})
