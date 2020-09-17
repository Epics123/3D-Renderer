workspace "3DRenderer"
	architecture "x86"
	startproject "3DRenderer"

	configurations
	{
		"Debug",
		"Release"
	}

outputdir = "%{cfg.buidlcfg}-%{cfg.system}-%{cfg.architecture}"

project "3DRenderer"
	location "3DRenderer"
	kind "WindowedApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "3DRenderer/src/pch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "RENDERER_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "RENDERER_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "RENDERER_DIST"
		runtime "Release"
		optimize "on"