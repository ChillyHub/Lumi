workspace "Lumi"
	architecture "x64"
	startproject "example"

	configurations
	{
	    "Debug",
	    "Release",
		"RelWithDebInfo",
	    "Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.architecture}" 

group "External"
	include "Lumi/ext/glad"
	include "Lumi/ext/GLFW"
	include "Lumi/ext/glm"
	include "Lumi/ext/imgui"
	include "Lumi/ext/spdlog"
	include "Lumi/ext/stb"
group ""

-- Include dirctories relative to root folder
IncludeDir = {}
IncludeDir["glad"] = "%{wks.location}/Lumi/ext/glad/include"
IncludeDir["GLFW"] = "%{wks.location}/Lumi/ext/GLFW/include"
IncludeDir["glm"] = "%{wks.location}/Lumi/ext/glm"
IncludeDir["ImGui"] = "%{wks.location}/Lumi/ext/imgui"
IncludeDir["spdlog"] = "%{wks.location}/Lumi/ext/spdlog/include"
IncludeDir["stb"] = "%{wks.location}/Lumi/ext/stb"

-- Include subpremake
include "Lumi"
include "example"
