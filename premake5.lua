workspace "Lumi"
	architecture "x64"
	startproject "LumiEditor"

	configurations
	{
	    "Debug",
	    "Release",
		"RelWithDebInfo",
	    "Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.architecture}" 

group "External"
	include "Lumi/ext/entt"
	include "Lumi/ext/glad"
	include "Lumi/ext/GLFW"
	include "Lumi/ext/glm"
	include "Lumi/ext/imgui"
	include "Lumi/ext/spdlog"
	include "Lumi/ext/stb"
	include "Lumi/ext/yaml"
group ""

-- Include dirctories relative to root folder
IncludeDir = {}
IncludeDir["entt"] = "%{wks.location}/Lumi/ext/entt/include"
IncludeDir["glad"] = "%{wks.location}/Lumi/ext/glad/include"
IncludeDir["GLFW"] = "%{wks.location}/Lumi/ext/GLFW/include"
IncludeDir["glm"] = "%{wks.location}/Lumi/ext/glm"
IncludeDir["ImGui"] = "%{wks.location}/Lumi/ext/imgui"
IncludeDir["spdlog"] = "%{wks.location}/Lumi/ext/spdlog/include"
IncludeDir["stb"] = "%{wks.location}/Lumi/ext/stb"
IncludeDir["yaml"] = "%{wks.location}/Lumi/ext/yaml/include"

-- Include subpremake
include "Lumi"
include "example"
include "LumiEditor"
