#pragma once
#include "Window/Window.h"

struct GLFWwindow;

namespace Nit
{
    class RenderingContext;

    class WindowsWindow : public Window
    {
    public:
        WindowsWindow(const WindowInitArgs& initArgs = {});
        WindowsWindow(const Window&) = delete;
        WindowsWindow& operator = (const WindowsWindow&) = delete;

        ~WindowsWindow() override;

        void* GetHandler() const override { return static_cast<void*>(m_WindowHandler); }

        void SetTitle(const std::string& title) override;
        const std::string& GetTitle() const override { return m_Title; }

        void GetSize(int* width, int* height) const override;

        void SetVSync(bool enabled) override;
        bool IsVSync() const override { return m_VSync; };

        void SetCursorMode(const CursorMode mode) override;
        CursorMode GetCursorMode() const override { return m_CursorMode; };

        bool IsOpened() const override;
        void Close() override;

        void Update();

    private:
        //void SetWindowCallbacks();

        std::string m_Title         = "";
        GraphicsAPI m_API           = GraphicsAPI::None;
        bool        m_VSync         = false;
        CursorMode  m_CursorMode    = CursorMode::Normal;
        GLFWwindow* m_WindowHandler = nullptr;
        bool        m_IsOpened      = false;
        
        std::unique_ptr<RenderingContext> m_RenderingContext;
    };
}