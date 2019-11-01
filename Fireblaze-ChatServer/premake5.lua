do
    local ProjectName = "Fireblaze-ChatServer"
    local BuildDir = "../bin/" .. outputdir .. "/" .. ProjectName
    local ObjDir = "../bin-int/" .. outputdir .. "/" .. ProjectName

    -- Path to Bolt install dir from project dir
    local BoltInstallDir = "../Bolt/"

    project (ProjectName)
        location ""
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++17"
        staticruntime "on"
        
        targetdir (BuildDir)
        objdir (ObjDir)

        pchheader "chatpch.h"
        pchsource "src/chatpch.cpp"
        
        files
        {
            "src/**.h",
            "src/**.hpp",
            "src/**.cpp"
        }
        
        includedirs
        {
            BoltInstallDir .. "%{IncludeDirs.GLFW}",
            BoltInstallDir .. "%{IncludeDirs.Glad}",
            BoltInstallDir .. "%{IncludeDirs.ImGui}",
            BoltInstallDir .. "%{IncludeDirs.spdlog}",
            BoltInstallDir .. "%{IncludeDirs.FreeTypeGL}",
            BoltInstallDir .. "%{IncludeDirs.FreeType}",
            BoltInstallDir .. "%{IncludeDirs.Lua}",
            BoltInstallDir .. "%{IncludeDirs.Python}",
            BoltInstallDir .. "%{IncludeDirs.Bolt}",
            "../%{IncludeDirs.FireblazeUtils}",
            "../%{IncludeDirs.FireblazeLoginServer}",
            "src"
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
                "BLT_BUILD_STATIC",
                "_CRT_SECURE_NO_WARNINGS",
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
end