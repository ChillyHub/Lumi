project "LumiEditor"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.hpp",
		"src/**.cpp"
	}

	includedirs
	{
		"%{wks.location}/Lumi/src",
		"%{wks.location}/Lumi/include",
		"%{wks.location}/LumiEditor",
		"%{wks.location}/LumiEditor/src",
		"%{IncludeDir.entt}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.ImGui}", 
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.yaml}"
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
    
    filter "configurations:RelWithDebInfo"
        defines "LUMI_RELEASE"
        defines "LM_PROFILE"
        runtime "RELEASE"
        optimize "on"