--premake5.lua
workspace "Engine"
    configurations { "Debug", "Release" }
    architecture "x86_64"
    cppdialect "C++17"

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "RELEASE" }
        optimize "On"

    filter "system:linux"
        defines { "LINUX" }

    filter "system:windows"
        defines { "WINDOWS" }

    filter { }

outputDir = "%{cfg.buildcfg}.%{cfg.system}.%{cfg.architecture}"

project "MyEngine"
    kind "SharedLib"
    language "C++"
    location "MyEngine"

    targetdir ("%{prj.location}/bin/" .. outputDir .. "/%{prj.name}")
    objdir ("%{prj.location}/obj/" .. outputDir .. "/%{prj.name}")

    files { 
        "%{prj.location}/src/**.cpp",
        "%{prj.location}/include/**.hpp"
    }

    includedirs{
        "%{prj.location}/include",
        "vendor/stb/include",
        "vendor/ImGui/include",
        "vendor/Glad/include"
    }

    links{
        "glfw",
        "GL", 
        "Glad",
        "ImGui",
        "stb"
    }

project "ImGui"
    kind "StaticLib"
    language "C++"
    location "vendor/%{prj.name}"
    targetdir ("MyEngine/bin/" .. outputDir .. "/%{prj.name}")
    objdir ("MyEngine/obj/" .. outputDir .. "/%{prj.name}")

    files { 
        "%{prj.location}/src/**.cpp",
        "%{prj.location}/include/**.h"
    }

    includedirs{
        "%{prj.location}/include",
        "vendor/Glad/include"
    }

    filter{"system:linux"}
        buildoptions{"-fPIC"}

    filter { }

project "stb"
    kind "StaticLib"
    language "C++"
    location "vendor/%{prj.name}"
    targetdir ("MyEngine/bin/" .. outputDir .. "/%{prj.name}")
    objdir ("MyEngine/obj/" .. outputDir .. "/%{prj.name}")

    files { 
        "%{prj.location}/src/**.cpp",
        "%{prj.location}/include/**.h"
    }

    includedirs{
        "%{prj.location}/include"
    }

    filter{"system:linux"}
        buildoptions{"-fPIC"}

    filter { }

project "Glad"
    kind "StaticLib"
    language "C++"
    location "vendor/%{prj.name}"
    targetdir ("MyEngine/bin/" .. outputDir .. "/%{prj.name}")
    objdir ("MyEngine/obj/" .. outputDir .. "/%{prj.name}")

    files { 
        "%{prj.location}/src/**.cpp",
        "%{prj.location}/src/**.c",
        "%{prj.location}/include/**.h"
    }

    includedirs{
        "%{prj.location}/include"
    }

    filter{"system:linux"}
        buildoptions{"-fPIC"}

    filter { }
