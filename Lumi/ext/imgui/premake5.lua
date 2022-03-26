project "ImGui"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
    staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	includedirs
	{
		".", 
		"%{IncludeDir.glad}",
		"%{IncludeDir.GLFW}",
	}

	files
	{
		"imconfig.h",
		"imgui.h",
		"imgui.cpp",
		"imgui_draw.cpp",
		"imgui_internal.h",
		"imgui_tables.cpp",
		"imgui_widgets.cpp",
		"imstb_rectpack.h",
		"imstb_textedit.h",
		"imstb_truetype.h",
		"imgui_demo.cpp",

		"backends/imgui_impl_glfw.h",
		"backends/imgui_impl_glfw.cpp", 
		"backends/imgui_impl_opengl3.h",
		"backends/imgui_impl_opengl3.cpp", 
		"backends/imgui_impl_opengl3_loader.h"
	}

	filter "system:windows"
		systemversion "latest"
		defines "IMGUI_IMPL_OPENGL_LOADER_CUSTOM"

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
