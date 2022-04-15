project "Lumi"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "src/pch.cpp"

	files
	{
		"src/**.h",
		"src/**.hpp",
		"src/**.cpp",
		"src/**.inl"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{wks.location}/%{prj.name}/src",
		"%{wks.location}/%{prj.name}",
		"%{IncludeDir.entt}",
        "%{IncludeDir.glad}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.stb}"
	}

	links
	{
		"opengl32.lib",
		"entt",
        "glad",
        "GLFW",
        "glm",
		"ImGui",
        "spdlog",
        "stb"
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
		runtime "RELEASE"
		optimize "on"

	filter "configurations:Dist"
		defines "LUMI_DIST"
		runtime "RELEASE"
		optimize "on"

    filter "configurations:RelWithDebInfo"
        defines "LUMI_RELEASE"
        defines "LM_PROFILE"
        runtime "RELEASE"
        optimize "on"