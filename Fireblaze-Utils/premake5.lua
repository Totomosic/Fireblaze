project "Fireblaze-Utils"
    location ""
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"
    
    targetdir (SolutionDir .. "bin/" .. outputdir .. "/Fireblaze-Utils")
    objdir (SolutionDir .. "bin-int/" .. outputdir .. "/Fireblaze-Utils")
    
    files
    {
        "src/**.h",
        "src/**.cpp",
        "src/**.hpp",
        "src/**.c"
    }
    
    includedirs
    {
        "../%{IncludeDirs.Bolt}",
        "../%{IncludeDirs.GLFW}",
        "../%{IncludeDirs.Glad}",
        "../%{IncludeDirs.ImGui}",
        "../%{IncludeDirs.spdlog}",
        "../%{IncludeDirs.FreeType}",
        "../%{IncludeDirs.FreeTypeGL}",
        "../%{IncludeDirs.Lua}",
        "src"
    }

    links
    {
        (BoltLibDir .. "Bolt-Core\\Bolt-Core.lib"),
        (BoltLibDir .. "FreeType\\FreeType.lib"),
        (BoltLibDir .. "FreeType-GL\\FreeType-GL.lib"),
        (BoltLibDir .. "Glad\\Glad.lib"),
        (BoltLibDir .. "GLFW\\GLFW.lib"),
        (BoltLibDir .. "ImGui\\ImGui.lib"),
        (BoltLibDir .. "Lua\\Lua.lib"),
        (BoltLibDir .. "GLFW\\GLFW.lib"),
        "opengl32.lib",
        "ws2_32.lib"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "BLT_PLATFORM_WINDOWS",
            "BLT_BUILD_STATIC"
        }

    filter "configurations:Debug"
        defines "BLT_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "BLT_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "BLT_DIST"
        runtime "Release"
        optimize "on"