project "stb"
    kind "StaticLib"
    language "C++"
	cppdialect "C++20"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "stb_image.h", 
        "stb_image.cpp"
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