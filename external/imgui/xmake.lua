local srcFiles = {
	"imgui.cpp",
	"imgui_draw.cpp",

	-- "imgui_tables.cpp",
	"imgui_widgets.cpp",
	"imgui_demo.cpp"
}

local hdrFiles = {
	"imconfig.h",
	"imgui.h",
	"imgui_internal.h",
	"imstb_rectpack.h",
	"imstb_textedit.h",
	"imstb_truetype.h",
}

if is_mode("dist") then
	set_optimize("fastest")
	set_symbols("hidden")
end

BuildProject({
	projectName = "ImGui",
	projectType = "static",
	macros = {},
	languages = {"cxx20"},
	depends = {},
	files = srcFiles,
	headerfiles = hdrFiles,
	pchHeader = nil,
	includePaths = {},
	packages = {},
	debugLink = {},
	releaseLink = {},
	link = {},
	afterBuildFunc = nil,
	enableException = true,
	staticruntime = true,
})