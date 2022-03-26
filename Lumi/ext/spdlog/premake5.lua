project "spdlog"
    kind "StaticLib"
    language "C++"
	cppdialect "C++20"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    includedirs
	{
		"include"
	}

    files
    {
        "include/spdlog/**.h",
		"include/spdlog/**.hpp",
		"include/spdlog/**.cpp", 
		"include/spdlog/**.inl",
        "src/**.cpp"
    }

    defines
    {
        "SPDLOG_COMPILED_LIB"
    }

    filter "system:windows"
		systemversion "latest"
    
    filter "system:linux"
		pic "On"
		systemversion "latest"
		cppdialect "C++20"
    
    filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"