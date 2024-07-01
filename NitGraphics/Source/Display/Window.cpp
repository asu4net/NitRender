#include "Window.h"
#include "Platform/Windows/WindowsWindow.h"

namespace Display
{
    std::unique_ptr<Window> Window::Create(const WindowCfg& initArgs /*= {}*/)
    {
        return std::make_unique<WindowsWindow>(initArgs);
    }
}