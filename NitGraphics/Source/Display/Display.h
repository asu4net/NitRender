#pragma once

#include "Window.h"

namespace Display
{
    void    CreateWindow(const WindowInitArgs& initArgs = {});
    Window& GetWindow();
    void    UpdateWindow();
    bool    IsWindowOpened();
    void    DestroyWindow();
}