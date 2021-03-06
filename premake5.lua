workspace "PEngine"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-${cfg.architecture}"

-- Include directories relative to root folder (Solution Directory)
IncludeDir = {}
IncludeDir["GLFW"] = "PEngine/vendor/GLFW/include"
IncludeDir["Glad"] = "PEngine/vendor/Glad/include"
IncludeDir["ImGui"] = "PEngine/vendor/imgui"
IncludeDir["glm"] = "PEngine/vendor/glm"

include "PEngine/vendor/GLFW"
include "PEngine/vendor/Glad"
include "PEngine/vendor/imgui"

project "PEngine"
	location "PEngine"
	kind "SharedLib"
	language "C++"

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "pepch.h"
	pchsource "PEngine/src/pepch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.ImGui}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"PE_PLATFORM_WINDOWS",
			"PE_BUILD_DLL",
			"GLFW_INCLUDE_NONE",
			"DLL_EXPORT=1"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

		filter "configurations:Release"
			defines "PE_RELEASE"
			buildoptions "/MD"
			optimize "On"

		filter "configurations:Debug"
			defines "PE_DEBUG"
			buildoptions "/MDd"
			symbols "On"


		filter "configurations:Dist"
			defines "PE_DIST"
			buildoptions "/MD"
			symbols "On"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-int/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"PEngine/vendor/spdlog/include",
		"%{IncludeDir.glm}",
		"PEngine/src",
		"PEngine/vendor"
	}

	links
	{
		"PEngine"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"PE_PLATFORM_WINDOWS"
		}

		filter "configurations:Release"
			defines "PE_RELEASE"
			optimize "On"

		filter "configurations:Debug"
			defines "PE_DEBUG"
			buildoptions "/MDd"
			symbols "On"


		filter "configurations:Dist"
			defines "PE_DIST"
			symbols "On"