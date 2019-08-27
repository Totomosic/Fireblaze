project "Fireblaze-ChatServer"
    location ""
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"
    
    targetdir (SolutionDir .. "bin/" .. outputdir .. "/Fireblaze-ChatServer")
    objdir (SolutionDir .. "bin-int/" .. outputdir .. "/Fireblaze-ChatServer")

    pchheader "chatpch.h"
    pchsource "src/chatpch.cpp"
    
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
        "../%{IncludeDirs.FireblazeUtils}",
        "../%{IncludeDirs.FireblazeLoginServer}",
        "src"
    }

    links
    {
        "opengl32.lib",
        "ws2_32.lib",
        "Fireblaze-Utils"
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