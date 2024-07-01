#include "Window.h"
#include "Platform/Windows/WindowsWindow.h"

namespace Graphics
{
    WindowUPtr Window::Create(const WindowInitArgs& initArgs /*= {}*/)
    {
        return std::make_unique<WindowsWindow>(initArgs);
    }
}