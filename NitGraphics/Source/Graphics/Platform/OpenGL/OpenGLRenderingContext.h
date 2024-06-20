#pragma once
#include "Graphics/RenderingContext.h"

struct GLFWwindow;

namespace Nit
{
    class OpenGLRenderingContext : public RenderingContext
    {
    public:
        inline static bool EnableDebugMessages = false;

        inline static std::function<void(const std::string& message)> OnDebugMessage = [](const std::string& message) {
            std::cout << "[OpenGL] %s " << message.c_str() << std::endl;
        };
        OpenGLRenderingContext(void* windowHandler);

        void SwapBuffers() const override;

    private:
        GLFWwindow* m_WindowHandler;
    };
}