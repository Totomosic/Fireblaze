workspace "Fireblaze"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

-- Path to directory containing Bolt-Core
InstallDir = "Bolt/"

include (InstallDir .. "Paths.lua")

group("Resources")
include (InstallDir .. ResourcesDir .. "Converter")
group ("Bolt/Vendor")
include (InstallDir .. BoltDir .. "vendor/GLFW")
include (InstallDir .. BoltDir .. "vendor/Glad")
include (InstallDir .. BoltDir .. "vendor/ImGui")
include (InstallDir .. BoltDir .. "vendor/spdlog")
include (InstallDir .. BoltDir .. "vendor/FreeType")
include (InstallDir .. BoltDir .. "vendor/FreeType-GL")
include (InstallDir .. BoltDir .. "vendor/Lua")
group("Bolt/Vendor/Python")
include (InstallDir .. BoltDir .. "vendor/Python/cpython/PCBuild")
group ("Bolt")
include (InstallDir .. BoltDir)

IncludeDirs["FireblazeUtils"] = "Fireblaze-Utils/src"
IncludeDirs["FireblazeLoginServer"] = "Fireblaze-LoginServer/src"
IncludeDirs["FireblazeGameServer"] = "Fireblaze-GameServer/src"
IncludeDirs["FireblazeChatServer"] = "Fireblaze-ChatServer/src"

group ("Fireblaze/Utils")
include ("Fireblaze-Utils")
group ("Fireblaze/Clients")
include ("Fireblaze")
group ("Fireblaze/Servers")
include ("Fireblaze-LoginServer")
include ("Fireblaze-GameServer")
include ("Fireblaze-ChatServer")