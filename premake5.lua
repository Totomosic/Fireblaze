workspace "Fireblaze"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Solution Directory
SolutionDir = "..\\"
-- Bolt Directory
BoltDir = "..\\Bolt\\Bolt-Engine\\"
BoltLibDir = "..\\..\\..\\Bolt\\bin\\Debug-windows-x86_64\\"
-- Projects Directory
ProjectsDir = ""

-- Include directories relative to solutions directory
IncludeDirs = {}
IncludeDirs["Bolt"] =       "..\\" .. BoltDir .. "Bolt-Core\\src"
IncludeDirs["GLFW"] =       "..\\" .. BoltDir .. "Bolt-Core\\vendor\\GLFW\\include"
IncludeDirs["Glad"] =       "..\\" .. BoltDir .. "Bolt-Core\\vendor\\Glad\\include"
IncludeDirs["ImGui"] =      "..\\" .. BoltDir .. "Bolt-Core\\vendor\\ImGui"
IncludeDirs["spdlog"] =     "..\\" .. BoltDir .. "Bolt-Core\\vendor\\spdlog\\include"
IncludeDirs["FreeTypeGL"] = "..\\" .. BoltDir .. "Bolt-Core\\vendor\\FreeType-GL"
IncludeDirs["FreeType"] =   "..\\" .. BoltDir .. "Bolt-Core\\vendor\\FreeType\\include"
IncludeDirs["Lua"] =        "..\\" .. BoltDir .. "Bolt-Core\\vendor\\Lua\\src"

IncludeDirs["FireblazeUtils"] = ProjectsDir .. "Fireblaze-Utils\\src"
IncludeDirs["FireblazeLoginServer"] = ProjectsDir .. "Fireblaze-LoginServer\\src"
IncludeDirs["FireblazeChatServer"] = ProjectsDir .. "Fireblaze-ChatServer\\src"

include (ProjectsDir .. "Fireblaze-Utils")
include (ProjectsDir .. "Fireblaze")
include (ProjectsDir .. "Fireblaze-LoginServer")
include (ProjectsDir .. "Fireblaze-ChatServer")