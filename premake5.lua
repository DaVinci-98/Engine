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
        "Vendor/stb/include",
        "Vendor/ImGui/include",
        "Vendor/Glad/include",
        "Modules/OpenGL/include",
        "Modules/EventSystem/include",
    }

    links{
        "glfw",
        "GL", 
        "Glad",
        "ImGui",
        "stb",
        "OpenGL",
        "EventSystem"
    }

project "OpenGL"
    kind "StaticLib"
    language "C++"
    
    location "Modules/%{prj.name}"
    targetdir ("MyEngine/bin/" .. outputDir .. "/%{prj.name}")
    objdir ("MyEngine/obj/" .. outputDir .. "/%{prj.name}")

    files {
        "%{prj.location}/src/**.cpp",
        "%{prj.location}/include/**.hpp"
    }

    includedirs{
        "%{prj.location}/include",
        "Vendor/Glad/include",
        "Vendor/stb/include"
    }

    filter{"system:linux"}
        buildoptions{"-fPIC"}

project "EventSystem"
    kind "StaticLib"
    language "C++"
    
    location "Modules/%{prj.name}"
    targetdir ("MyEngine/bin/" .. outputDir .. "/%{prj.name}")
    objdir ("MyEngine/obj/" .. outputDir .. "/%{prj.name}")

    files {
        "%{prj.location}/src/**.cpp",
        "%{prj.location}/include/**.hpp"
    }

    includedirs{
        "%{prj.location}/include",
        "Vendor/Glad/include"
    }

    filter{"system:linux"}
        buildoptions{"-fPIC"}

project "ImGui"
    kind "StaticLib"
    language "C++"
    location "Vendor/%{prj.name}"
    targetdir ("MyEngine/bin/" .. outputDir .. "/%{prj.name}")
    objdir ("MyEngine/obj/" .. outputDir .. "/%{prj.name}")

    files { 
        "%{prj.location}/src/**.cpp",
        "%{prj.location}/include/**.h"
    }

    includedirs{
        "%{prj.location}/include",
        "Vendor/Glad/include"
    }

    filter{"system:linux"}
        buildoptions{"-fPIC"}

    filter { }

project "stb"
    kind "StaticLib"
    language "C++"
    location "Vendor/%{prj.name}"
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
    location "Vendor/%{prj.name}"
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
