#pragma once
#include "Graphics/RenderAPI.h"

namespace Graphics
{
    class VertexArray;

    class OpenGLRenderAPI : public RenderAPI
    {
    public:
        OpenGLRenderAPI() = default;
        ~OpenGLRenderAPI() override = default;

        void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) const override;
        void SetClearColor(const glm::vec4& clearColor) const override;
        void ClearScreen() const override;
        void SetBlendingEnabled(bool bEnabled) const override;
        void SetBlendingMode(const BlendingMode blendingMode) const override;
        void DrawElements(const std::shared_ptr<VertexArray>& vertexArray, uint32_t elementCount) const override;
        void SetDepthTestEnabled(bool bEnabled) const override;
    };
}