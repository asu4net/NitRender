project "NitRender"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    targetdir (binariesdir)
    objdir (intermediatesdir)
    pchheader "NitRenderPCH.h"
    pchsource "Source/NitRenderPCH.cpp"
    forceincludes { "NitRenderPCH.h" }

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