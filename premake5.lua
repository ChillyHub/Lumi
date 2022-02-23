workspace "Lumi"
	architecture "x64"
	startproject "example"

	configurations
	{
	    "Debug",
	    "Release",
	    "Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.architecture}" 

-- Include dirctories relative to root folder
IncludeDir = {}
IncludeDir["GLFW"] = "Lumi/lib/GLFW/include"
IncludeDir["glad"] = "Lumi/lib/glad/include"
IncludeDir["ImGui"] = "Lumi/lib/imgui"
IncludeDir["glm"] = "Lumi/lib/glm"
IncludeDir["stb"] = "Lumi/lib/stb"

-- Include subpremake
include "Lumi/lib/GLFW"
include "Lumi/lib/glad"
include "Lumi/lib/imgui"

project "Lumi"
	location "Lumi"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "Lumi/src/pch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.inl"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/lib/spdlog/include",
		"%{prj.name}/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb}"
	}

	links
	{
		"GLFW",
		"opengl32.lib",
		"glad",
		"ImGui"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"_LM_WINDOWS_",
			"LM_DLL_EXPORTS"
		}

	filter "configurations:Debug"
		defines "LUMI_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "LUMI_RELEASE"
		runtime "Debug"
		optimize "on"

	filter "configurations:Dist"
		defines "LUMI_DIST"
		runtime "Debug"
		optimize "on"

project "example"
	location "example"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Lumi/lib/spdlog/include",
		"Lumi/src",
		"%{IncludeDir.glm}",
		"%{IncludeDir.ImGui}"
	}
 
	links
	{
		"Lumi"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"_LM_WINDOWS_"
		}

	filter "configurations:Debug"
		defines "LUMI_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "LUMI_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "LUMI_DIST"
		runtime "Release"
		optimize "on"
