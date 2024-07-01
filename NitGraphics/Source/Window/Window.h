#pragma once

namespace Graphics
{
    enum class CursorMode { Normal, Disabled, Hidden, Captured };

    struct WindowInitArgs
    {
        std::string title           = "Nit Window";
        int         width           = 1280; 
        int         height          = 720;
        GraphicsAPI API             = GraphicsAPI::OpenGL;
        bool        vSync           = true;
        bool        bStartMaximized = false;
        CursorMode  cursorMode  = CursorMode::Normal;
    };

    using WindowUPtr = std::unique_ptr<class Window>;

    class Window
    {
    public:
        static WindowUPtr Create(const WindowInitArgs& initArgs = {});

        virtual ~Window() = default;

        virtual void* GetHandler() const = 0;

        virtual void SetTitle(const std::string& title) = 0;
        virtual const std::string& GetTitle() const = 0;

        virtual void GetSize(int* width, int* height) const = 0;

        virtual void SetVSync(bool enabled) = 0;
        virtual bool IsVSync() const = 0;

        virtual void SetCursorMode(const CursorMode mode) = 0;
        virtual CursorMode GetCursorMode() const = 0;

        virtual bool IsOpened() const = 0;

        virtual void Close() = 0;

        virtual void Update() = 0;        
    };
}