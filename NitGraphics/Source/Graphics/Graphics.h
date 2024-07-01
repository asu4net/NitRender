#pragma once
#include "RenderAPI.h"

namespace Graphics
{
    struct RenderInitArgs
    {
        API graphicsAPI = API::OpenGL;
    };

    API GetGraphicsAPI();
    std::shared_ptr<RenderAPI>  GetRenderAPI();

    void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
    void SetClearColor(const glm::vec4& clearColor);
    void ClearScreen();
    void SetBlendingEnabled(bool bEnabled);
    void SetBlendingMode(const BlendingMode blendingMode);
    void DrawElements(const std::shared_ptr<VertexArray>& vertexArray, uint32_t elementCount);
    void SetDepthTestEnabled(bool bEnabled);

    void CreateRenderContext(const RenderInitArgs args = {});
    void DestroyRenderContext();
}