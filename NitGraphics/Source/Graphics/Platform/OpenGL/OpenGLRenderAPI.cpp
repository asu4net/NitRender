#include "OpenGLRenderAPI.h"
#include "Graphics/VertexObject.h"
#include <glad/glad.h>

namespace Graphics
{
    void OpenGLRenderAPI::SetViewport(const uint32_t x, const uint32_t y, const uint32_t width, const uint32_t height) const
    {
        glViewport(x, y, width, height);
    }

    void OpenGLRenderAPI::SetClearColor(const glm::vec4& clearColor) const
    {
        glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
    }

    void OpenGLRenderAPI::ClearScreen() const
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRenderAPI::SetBlendingEnabled(const bool bEnabled) const
    {
        if (bEnabled) glEnable(GL_BLEND);
        else glDisable(GL_BLEND);
    }

    void OpenGLRenderAPI::SetBlendingMode(const BlendingMode blendingMode) const
    {
        switch (blendingMode) {
        case BlendingMode::Solid:
            glBlendFunc(GL_ONE, GL_ZERO);
            break;
        case BlendingMode::Alpha:
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            break;
        case BlendingMode::Add:
            glBlendFunc(GL_SRC_ALPHA, GL_ONE);
            break;
        case BlendingMode::Multiply:
            glBlendFunc(GL_DST_COLOR, GL_ZERO);
            break;
        }
    }

    void OpenGLRenderAPI::DrawElements(const std::shared_ptr<VertexArray>& vertexArray, const uint32_t elementCount) const
    {
        vertexArray->Bind();
        glDrawElements(GL_TRIANGLES, elementCount, GL_UNSIGNED_INT, nullptr);
        vertexArray->Unbind();
    }

    void OpenGLRenderAPI::SetDepthTestEnabled(const bool bEnabled) const
    {
        if (bEnabled) glEnable(GL_DEPTH_TEST);
        else glDisable(GL_DEPTH_TEST);
    }
}