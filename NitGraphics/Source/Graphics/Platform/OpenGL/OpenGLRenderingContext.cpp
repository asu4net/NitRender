#include "OpenGLRenderingContext.h"
#include <glad/glad.h>
#include <glfw/glfw3.h>

namespace Graphics
{
    void APIENTRY OnDebugMessageCallback(GLenum source, GLenum type, unsigned int id, GLenum severity,
        GLsizei length, const char* message, const void* userParam)
    {
        if (!OpenGLRenderingContext::EnableDebugMessages) return;
        OpenGLRenderingContext::OnDebugMessage(message);
    }

    OpenGLRenderingContext::OpenGLRenderingContext(void* windowHandler)
        : m_windowHandler(static_cast<GLFWwindow*>(windowHandler))
    {
        if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
        {
            assert(false && "Failed to initialize glad!");
            return;
        }

        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(OnDebugMessageCallback, nullptr);
    }

    void OpenGLRenderingContext::SwapBuffers() const
    {
        glfwSwapBuffers(m_windowHandler);
    }
}