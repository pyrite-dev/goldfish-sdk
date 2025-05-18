require("gmake")
if premake.modules.gmake.cpp.pchRules and not(premake.modules.gmake.patched_resource) then
	premake.modules.gmake.patched_resource = true
	premake.override(premake.modules.gmake.cpp, "pchRules", function(base, cfg, toolset)
		base(cfg, toolset)
		_p("$(RESOURCES): | prebuild")
	end)
end

flags("MultiProcessorCompile")

workspace("GoldFishSDK")
	configurations({
		"Debug",
		"Release"
	})
	platforms({
		"Native",
		"Win32",
		"Win64"
	})
	defaultplatform("Native")

filter("platforms:Win32")
	system("windows")
	architecture("x86")
	gccprefix("i686-w64-mingw32-")

filter("platforms:Win64")
	system("windows")
	architecture("x86_64")
	gccprefix("x86_64-w64-mingw32-")

filter({})

include "engine"

project("SDK")
	flags("RelativeLinks")
	kind("WindowedApp")
	language("C")
	targetdir("bin/%{cfg.buildcfg}/%{cfg.platform}")
	objdir("obj/%{cfg.buildcfg}/%{cfg.platform}")
	targetname("sdk")
	includedirs({
		"engine/include",
		"include",
		"external/imgui",
		"external/stb"
	})
	files({
		"src/*.c",
		"src/*.cpp",
		"external/imgui/*.cpp"
	})
	filter({"options:opengl=rgfw"})
		defines("DONT_RGFW")
	filter({})
	links({
		"GoldFish"
	})
	filter({
		"system:windows",
		"toolset:gcc or toolset:clang"
	})
		links({
			"stdc++:static"
		})
	filter({"system:windows"})
		links({
			"opengl32",
			"glu32",
			"winmm"
		})
	filter({"system:not windows"})
		links({
			"GLU"
		})
	filter({})
	-- Call this if you are gonna use my engine...
	gf_link_stuffs("options:engine=static")
	filter("configurations:Debug")
		defines({
			"DEBUG"
		})
		symbols("On")
	filter("configurations:Release")
		defines({
			"NDEBUG"
		})
		optimize("On")
