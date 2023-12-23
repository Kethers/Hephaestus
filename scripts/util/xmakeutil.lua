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

	targetdir = config.targetdir
	if targetdir ~= nil then
		set_targetdir(targetdir)
	else
		set_targetdir("$(buildir)/bin/$(mode)-$(plat)-$(arch)/" .. config.projectName)
	end

	if config.group then
		set_group(config.group)
	end
	
	set_objectdir("$(buildir)/bin-int/$(mode)-$(plat)-$(arch)/" .. config.projectName)
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

	Execute(config.customRules, add_rules)
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
