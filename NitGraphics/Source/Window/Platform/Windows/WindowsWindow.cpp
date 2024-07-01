#include "WindowsWindow.h"
#include <glfw/glfw3.h>
#include "Graphics/RenderingContext.h"

namespace Graphics
{
    WindowsWindow::WindowsWindow(const WindowInitArgs& initArgs)
    {
        bool bInited = glfwInit();
        assert(bInited && "GLFW Window initialisation failed!");

        if (!bInited) return;

        m_windowHandler = glfwCreateWindow(initArgs.width, initArgs.height, initArgs.title.c_str(), nullptr, nullptr);

        assert(m_windowHandler && "GLFW Window creation failed!");

        glfwMakeContextCurrent(m_windowHandler);

        m_RenderingContext = RenderingContext::Create(m_windowHandler);

        m_bIsOpened = true;

        SetVSync(initArgs.vSync);
        SetTitle(initArgs.title);
        SetCursorMode(initArgs.cursorMode);
        //SetWindowCallbacks();

        if (initArgs.bStartMaximized)
        {
            glfwSetWindowAttrib(m_windowHandler, GLFW_MAXIMIZED, GLFW_TRUE);
            glfwMaximizeWindow(m_windowHandler);
        }
    }

    WindowsWindow::~WindowsWindow()
    {
        if (IsOpened())
            Close();

        assert(m_windowHandler && "GLFW Window handler empty!");
        glfwDestroyWindow(m_windowHandler);
        m_windowHandler = nullptr;
        glfwTerminate();
    }

    //TODO: Finish
    void WindowsWindow::SetTitle(const std::string& title)
    {
        m_title = title;
        glfwSetWindowTitle(m_windowHandler, title.c_str());
    }

    void WindowsWindow::GetSize(int* width, int* height) const
    {
        glfwGetWindowSize(m_windowHandler, width, height);
    }

    //TODO: Finish
    void WindowsWindow::SetVSync(bool enabled)
    {
        glfwSwapInterval(enabled ? 1 : 0);
        m_vSync = enabled;
    }

    //TODO: Finish
    void WindowsWindow::SetCursorMode(const CursorMode mode)
    {
        m_cursorMode = mode;

        switch (m_cursorMode)
        {
        case CursorMode::Normal:
            glfwSetInputMode(m_windowHandler, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            return;
        case CursorMode::Disabled:
            glfwSetInputMode(m_windowHandler, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            return;
        case CursorMode::Hidden:
            glfwSetInputMode(m_windowHandler, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
            return;
        case CursorMode::Captured:
            glfwSetInputMode(m_windowHandler, GLFW_CURSOR, GLFW_CURSOR_CAPTURED);
        }
    }

    bool WindowsWindow::IsOpened() const
    {
        return m_bIsOpened && !glfwWindowShouldClose(m_windowHandler);
    }

    void WindowsWindow::Close()
    {
        assert(m_bIsOpened && "Window is already closed!");
        m_bIsOpened = false;
    }

    void WindowsWindow::Update()
    {
        glfwPollEvents();
        m_RenderingContext->SwapBuffers();
    }

    //---------------------------------------------------------
    // GLFW CALLBACKS
    //---------------------------------------------------------

    /*static WindowEvents& GetEvents(GLFWwindow* windowHandler)
    {
        static WindowEvents* events = static_cast<WindowEvents*>(glfwGetWindowUserPointer(windowHandler));
        return *events;
    }

    void WindowSizeCallback(GLFWwindow* windowHandler, const int width, const int height) { GetEvents(windowHandler).CallResizeEvent(width, height); }
    void WindowCloseCallback(GLFWwindow* windowHandler) { GetEvents(windowHandler).CallCloseEvent(); }
    void WindowKeyPressedCallback(GLFWwindow* windowHandler, const int key, const bool pressed) { GetEvents(windowHandler).CallKeyPressedEvent(key, pressed); }
    void WindowKeyReleasedCallback(GLFWwindow* windowHandler, const int key) { GetEvents(windowHandler).CallKeyReleasedEvent(key); }
    void WindowCursorPosCallback(GLFWwindow* windowHandler, const Vector2& pos) { GetEvents(windowHandler).CallCursorPosEvent(pos); }
    void WindowMouseButtonPressedCallback(GLFWwindow* windowHandler, const int mouseButton, const bool pressed) { GetEvents(windowHandler).CallMouseButtonPressedEvent(mouseButton, pressed); }
    void WindowMouseButtonReleasedCallback(GLFWwindow* windowHandler, const int mouseButton) { GetEvents(windowHandler).CallMouseButtonReleasedEvent(mouseButton); }
    void WindowScrollCallback(GLFWwindow* windowHandler, const Vector2& offset) { GetEvents(windowHandler).CallScrollEvent(offset); }

    void WindowsWindow::SetWindowCallbacks()
    {
        glfwSetWindowUserPointer(m_WindowHandler, &m_Events);

        glfwSetWindowSizeCallback(m_WindowHandler, WindowSizeCallback);
        glfwSetWindowCloseCallback(m_WindowHandler, WindowCloseCallback);
        glfwSetKeyCallback(m_WindowHandler, [](GLFWwindow* windowHandler, const int key, const int scanCode, const int action, const int mods)
            {
                switch (action)
                {
                case GLFW_PRESS:
                    WindowKeyPressedCallback(windowHandler, key, false);
                    return;
                case GLFW_RELEASE:
                    WindowKeyReleasedCallback(windowHandler, key);
                    return;
                case GLFW_REPEAT:
                    WindowKeyPressedCallback(windowHandler, key, true);
                }
            });
        glfwSetCursorPosCallback(m_WindowHandler, [](GLFWwindow* windowHandler, const double xPos, const double yPos)
            {
                const Vector2 cursorPosition = { static_cast<float>(xPos), static_cast<float>(yPos) };
                WindowCursorPosCallback(windowHandler, cursorPosition);
            });
        glfwSetMouseButtonCallback(m_WindowHandler, [](GLFWwindow* windowHandler, const int button, const int action, const int mods)
            {
                switch (action)
                {
                case GLFW_PRESS:
                    WindowMouseButtonPressedCallback(windowHandler, button, false);
                    return;
                case GLFW_RELEASE:
                    WindowMouseButtonReleasedCallback(windowHandler, button);
                    return;
                case GLFW_REPEAT:
                    WindowMouseButtonPressedCallback(windowHandler, button, true);
                }
            });
        glfwSetScrollCallback(m_WindowHandler, [](GLFWwindow* windowHandler, const double xOffset, const double yOffset)
            {
                const Vector2 offset = { static_cast<float>(xOffset), static_cast<float>(yOffset) };
                WindowScrollCallback(windowHandler, offset);
            });
    }*/
}