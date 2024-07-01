#pragma once
#include "RenderAPI.h"
#include "Window/Window.h"

namespace Graphics
{
    struct RenderInitArgs
    {
        WindowInitArgs WindowSettings;
        GraphicsAPI    API = GraphicsAPI::OpenGL;
    };

    GraphicsAPI                 GetGraphicsAPI();
    std::shared_ptr<RenderAPI>  GetRenderAPI();
    Window&                     GetWindow();
    bool                        IsWindowOpened();
    void                        UpdateWindow();

    void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
    void SetClearColor(const glm::vec4& clearColor);
    void ClearScreen();
    void SetBlendingEnabled(bool bEnabled);
    void SetBlendingMode(const BlendingMode blendingMode);
    void DrawElements(const std::shared_ptr<VertexArray>& vertexArray, uint32_t elementCount);
    void SetDepthTestEnabled(bool bEnabled);

    void InitGraphics(const RenderInitArgs args = {});
    void FinishGraphics();
}