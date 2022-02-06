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

-- Include subpremake
include "Lumi/lib/GLFW"
include "Lumi/lib/glad"
include "Lumi/lib/imgui"

project "Lumi"
	location "Lumi"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

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
		"%{IncludeDir.glad}",
		"%{IncludeDir.ImGui}"
	}

	links
	{
		"GLFW",
		"opengl32.lib",
		"glad",
		"ImGui"
	}

	filter "system:windows"
		cppdialect "C++20"
		systemversion "latest"

		defines
		{
			"_LM_WINDOWS_",
			"LM_DLL_EXPORTS",
			"IMGUI_IMPL_OPENGL_LOADER_CUSTOM"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/example")
		}

	filter "configurations:Debug"
		defines "LUMI_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "LUMI_RELEASE"
		runtime "Debug"
		optimize "On"

	filter "configurations:Dist"
		defines "LUMI_DIST"
		runtime "Debug"
		optimize "On"

project "example"
	location "example"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

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
		systemversion "latest"

		defines
		{
			"_LM_WINDOWS_"
		}

	filter "configurations:Debug"
		defines "LUMI_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "LUMI_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "LUMI_DIST"
		runtime "Release"
		optimize "On"