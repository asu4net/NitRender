outputdir                      = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
binariesdir                    = "%{wks.location}/Binaries/"              .. outputdir .. "/%{prj.name}"
intermediatesdir               = "%{wks.location}/Binaries-Intermediate/" .. outputdir .. "/%{prj.name}"

IncludeDirs                    = {}
IncludeDirs["NitGraphics"]     = "%{wks.location}/NitGraphics/Source"
IncludeDirs["glfw"]            = "%{wks.location}/ThirdParty/glfw/include"
IncludeDirs["glm"]             = "%{wks.location}/ThirdParty/glm"
IncludeDirs["glad"]            = "%{wks.location}/ThirdParty/glad/include"
IncludeDirs["stb"]             = "%{wks.location}/ThirdParty/stb/include"