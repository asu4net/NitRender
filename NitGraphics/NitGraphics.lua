project "NitGraphics"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    targetdir (binariesdir)
    objdir (intermediatesdir)
    pchheader "NitGraphicsPCH.h"
    pchsource "Source/NitGraphicsPCH.cpp"
    forceincludes { "NitGraphicsPCH.h" }

    includedirs 
    { 
        "Source",
        "%{IncludeDirs.glfw}",
        "%{IncludeDirs.glad}",
        "%{IncludeDirs.glm}",
        "%{IncludeDirs.stb}"
    }
    
    links
    {
        "glfw",
        "glad",
        "opengl32.lib"
    }

    files { "**.h", "**.cpp" }

    filter "files:**.natvis"
        buildaction "Natvis"

    filter "configurations:Debug"
        symbols "On"

    filter "configurations:Release"
        optimize "On"

    filter "system:windows"
        systemversion "latest"