#pragma once

namespace Display
{
    enum class CursorMode { Normal, Disabled, Hidden, Captured };

    struct WindowCfg
    {
        std::string   title           = "Nit Window";
        int           width           = 1280; 
        int           height          = 720;
        Graphics::API API             = Graphics::API::OpenGL;
        bool          vSync           = true;
        bool          bStartMaximized = false;
        CursorMode    cursorMode      = CursorMode::Normal;
    };

    class Window
    {
    public:
        static std::unique_ptr<Window> Create(const WindowCfg& initArgs = {});

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