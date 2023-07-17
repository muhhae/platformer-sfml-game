-- premake5.lua
workspace "SFMLGame"
    configurations { "Debug", "Release" }

SRCDIR = "src"

project "SFMLGame"
    kind "WindowedApp"
    language "C++"
    buildoptions {"-std=c++23", "-Wall"}
    linkoptions {"-lsfml-graphics", "-lsfml-window", "-lsfml-system"}

    targetdir "bin/%{cfg.buildcfg}"
    objdir "obj/%{cfg.buildcfg}"

    files {
        "%{SRCDIR}/**.h",
        "%{SRCDIR}/**.hpp", 
        "%{SRCDIR}/**.cpp"
    }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"