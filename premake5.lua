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

-- Include subpremake
include "Lumi/lib/GLFW"
include "Lumi/lib/glad"

project "Lumi"
	location "Lumi"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "Lumi/src/pch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
        "%{prj.name}/src/**.hpp",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/lib/spdlog/include",
		"%{prj.name}/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.glad}"
	}

	links
	{
		"GLFW",
		"opengl32.lib",
		"glad"
	}

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"_LM_WINDOWS_",
			"LM_DLL_EXPORTS"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/example")
		}

	filter "configurations:Debug"
		defines "LUMI_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "LUMI_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "LUMI_DIST"
		buildoptions "/MD"
		optimize "On"

project "example"
	location "example"
	kind "ConsoleApp"
	language "C++"

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
		"Lumi/src"
	}
 
	links
	{
		"Lumi"
	}

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"_LM_WINDOWS_"
		}

	filter "configurations:Debug"
		defines "LUMI_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "LUMI_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "LUMI_DIST"
		buildoptions "/MD"
		optimize "On"