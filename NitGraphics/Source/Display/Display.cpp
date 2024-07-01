#include "Display.h"

namespace Display
{
    std::unique_ptr<Window> g_window;

    void CreateWindow(const WindowCfg& cfg)
    {
        g_window = Window::Create(cfg);
    }

    Window& GetWindow()
    {
        assert(g_window);
        return *g_window.get();
    }

    void UpdateWindow()
    {
        assert(g_window);
        g_window->Update();
    }

    bool IsWindowOpened()
    {
        assert(g_window);
        return g_window->IsOpened();
    }

    void DestroyWindow()
    {
        assert(g_window);
        g_window.reset();
    }
}