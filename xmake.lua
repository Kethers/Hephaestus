set_xmakever("2.8.5")

add_rules("mode.debug", "mode.release")
add_rules("plugin.vsxmake.autoupdate")

set_allowedarchs("x64")
set_allowedplats("windows")
set_allowedmodes("debug", "release", "dist")

if is_os("windows") then
	add_defines("HEP_PLATFORM_WINDOWS", "UNICODE", "NOMINMAX")
end

if is_mode("debug") then
	add_defines("_DEBUG")
	add_defines("HEP_DEBUG")
elseif is_mode("release") then	-- bulitin release mode has defined "NDEBUG"
	add_defines("HEP_RELEASE")
elseif is_mode("dist") then
	add_defines("HEP_DIST", "NDEBUG")
	set_optimize("fastest")
	set_symbols("hidden")
end

option("solution_name")
	set_default("Hephaestus")
	set_values("Hephaestus", "Sandbox")
	set_showmenu(true)
option_end()

includes("scripts/util/xmakeutil.lua")

if is_config("solution_name", "Hephaestus") then
	includes("scripts/solutions/Hephaestus")
elseif is_config("solution_name", "Sandbox") then
	includes("scripts/solutions/Sandbox")
end
