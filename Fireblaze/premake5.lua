project "Fireblaze"
    location ""
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"
    
    targetdir (SolutionDir .. "bin/" .. outputdir .. "/Fireblaze")
    objdir (SolutionDir .. "bin-int/" .. outputdir .. "/Fireblaze")

    pchheader ("clientpch.h")
    pchsource ("src/clientpch.cpp")
    
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
        "src",
        "../Fireblaze-LoginServer/src"
    }

    links
    {
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