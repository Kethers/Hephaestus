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
	add_defines("HEP_DIST")
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

	set_languages("clatest", "cxx20")
	set_targetdir("$(buildir)/bin/$(mode)-$(plat)-$(arch)/" .. config.projectName)
	-- set_objectdir("$(buildir)/bin-int/$(mode)-$(plat)-$(arch)/" .. config.projectName)
	projectType = config.projectType
	if projectType ~= nil then
		set_kind(projectType)
	end

	pchHeader = config.pchHeader
	if pchHeader ~= nil then
		set_pcxxheader(pchHeader)
	end

	Execute(config.macros, add_defines)
	Execute(config.files, add_files)
	Execute(config.includePaths, add_includedirs)
	Execute(config.headerfiles, add_headerfiles)
	Execute(config.depends, add_deps)
	Execute(config.link, add_links)

	if is_mode("release") then
		Execute(config.releaseLink, add_links)
		set_optimize("fastest")
		if is_plat("windows") then
			set_runtimes("MD")
			add_cxflags("/Zi", "/W0", "/MP", "/Ob2", "/Oi", "/Ot", "/Oy", "/GT", "/GF", "/GS-", "/Gy", "/arch:AVX2",
				"/fp:precise", "/Gr", "/TP", {
					force = true
				})
			SetException(config)
		end
	else
		Execute(config.debugLink, add_links)
		set_optimize("none")
		if is_plat("windows") then
			set_runtimes("MDd")
			add_cxflags("/Zi", "/W0", "/MP", "/Ob0", "/Oy-", "/GF", "/GS", "/arch:AVX2", "/fp:precise", "/Gr", "/TP", {
				force = true
			})
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


BuildProject({
	projectName = "Hephaestus",
	projectType = "shared",
	macros = {"HEP_BUILD_DLL"},
	depends = {},
	files = {"Hephaestus/src/**.cpp"},
	headerfiles = {"Hephaestus/src/**.h"},
	pchHeader = "Hephaestus/src/heppch.h",
	includePaths = {"external"},
	debugLink = {},
	releaseLink = {},
	link = {"kernel32", "User32", "Gdi32", "Shell32"},
	afterBuildFunc = function (target)
		os.cp(target:targetfile(), target:targetdir() .. "/../Sandbox/" .. target:filename())
	end,
	enableException = true,
})

BuildProject({
	projectName = "Sandbox",
	projectType = "binary",
	macros = {},
	depends = {"Hephaestus"},
	files = {"Sandbox/src/**.cpp"},
	headerfiles = {"Sandbox/src/**.h"},
	pchHeader = nil,
	includePaths = {"external", "Hephaestus/src"},
	debugLink = {},
	releaseLink = {},
	link = {"kernel32", "User32", "Gdi32", "Shell32"},
	afterBuildFunc = nil,
	enableException = true,
})
