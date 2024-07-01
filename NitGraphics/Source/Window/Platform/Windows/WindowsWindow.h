#pragma once
#include "Window/Window.h"

struct GLFWwindow;

namespace Graphics
{
    class RenderingContext;

    class WindowsWindow : public Window
    {
    public:
        WindowsWindow(const WindowInitArgs& initArgs = {});
        WindowsWindow(const Window&) = delete;
        WindowsWindow& operator = (const WindowsWindow&) = delete;

        ~WindowsWindow() override;

        void* GetHandler() const override { return static_cast<void*>(m_windowHandler); }

        void SetTitle(const std::string& title) override;
        const std::string& GetTitle() const override { return m_title; }

        void GetSize(int* width, int* height) const override;

        void SetVSync(bool enabled) override;
        bool IsVSync() const override { return m_vSync; };

        void SetCursorMode(const CursorMode mode) override;
        CursorMode GetCursorMode() const override { return m_cursorMode; };

        bool IsOpened() const override;
        void Close() override;

        void Update();

    private:
        //void SetWindowCallbacks();

        std::string m_title         = "";
        GraphicsAPI m_API           = GraphicsAPI::None;
        bool        m_vSync         = false;
        CursorMode  m_cursorMode    = CursorMode::Normal;
        GLFWwindow* m_windowHandler = nullptr;
        bool        m_bIsOpened      = false;
        
        std::unique_ptr<RenderingContext> m_RenderingContext;
    };
}