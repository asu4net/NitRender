project "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    targetdir (binariesdir)
    objdir (intermediatesdir)

    includedirs 
    { 
        "Source",
        "%{IncludeDirs.NitRender}",
        "%{IncludeDirs.glm}"
    }
    
    links
    {
        "NitRender"
    }

    files { "**.h", "**.cpp" }

    filter "configurations:Debug"
        symbols "On"

    filter "configurations:Release"
        optimize "On"

    filter "system:windows"
        systemversion "latest"