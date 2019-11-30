workspace "Fireblaze"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

-- Path to directory containing Bolt-Core
BoltDir = "Bolt/"

include (BoltDir .. "BoltInclude.lua")

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