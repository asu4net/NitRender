#pragma once

#include "Window.h"

namespace Display
{
    void    CreateWindow(const WindowCfg& cfg = {});
    Window& GetWindow();
    void    UpdateWindow();
    bool    IsWindowOpened();
    void    DestroyWindow();
}