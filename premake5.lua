-- premake5.lua
-- created by muhhae

include ("staticlib.lua") --for vcpkg to choose static library for linking

workspace "App"
    configurations { "Debug", "Release" }
    platforms { "x64" }

project "App"
    kind "ConsoleApp" --App Type
    language "C++" --Languange

    cppdialect "C++latest"

    targetdir "bin/%{cfg.buildcfg}" 
    objdir "obj/%{cfg.buildcfg}"

    files { 
        "App/**.cpp",
    }

    includedirs {
        "App",
    }
    
    links {
        "winmm", "gdi32"
    }

    staticruntime "On" --static runtime for msvc
    dpiawareness "HighPerMonitor" --high dpi awareness for msvc
    flags {
        "MultiProcessorCompile" --multi processor compile for msvc
    }
    
    defines { "SFML_STATIC" } --static sfml

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "RELEASE" }
        optimize "On"