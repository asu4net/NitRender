workspace "NitGraphics"
    architecture "x86_64"
    configurations { "Debug", "Release" }
    startproject "Sandbox"

include "Directories.lua"

include "NitGraphics/NitGraphics.lua"
include "Sandbox/Sandbox.lua"

group "ThirdParty"
    include "ThirdParty/glfw/glfw.lua"
    include "ThirdParty/glad/glad.lua"
group ""