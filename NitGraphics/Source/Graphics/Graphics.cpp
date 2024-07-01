#include "Graphics.h"
#include "RenderAPI.h"

namespace Graphics
{
    struct GraphicsContext
    {
        GraphicsAPI   graphicsAPI = GraphicsAPI::None;
        std::shared_ptr<RenderAPI> renderAPI = nullptr;
        std::unique_ptr<Window>    window = nullptr;
    };

    GraphicsContext* g_context = nullptr;

    GraphicsAPI    GetGraphicsAPI() { assert(g_context); return g_context->graphicsAPI; }
    std::shared_ptr<RenderAPI>  GetRenderAPI() { assert(g_context); return g_context->renderAPI; }
    Window& GetWindow() { assert(g_context && g_context->window); return *g_context->window; }
    bool           IsWindowOpened() { return GetWindow().IsOpened(); }
    void           UpdateWindow() { GetWindow().Update(); }

    void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
    {
        GetRenderAPI()->SetViewport(x, y, width, height);
    }

    void SetClearColor(const glm::vec4& clearColor)
    {
        GetRenderAPI()->SetClearColor(clearColor);
    }

    void ClearScreen()
    {
        GetRenderAPI()->Clear();
    }

    void SetBlendingEnabled(bool bEnabled)
    {
        GetRenderAPI()->SetBlendingEnabled(bEnabled);
    }

    void SetBlendingMode(const BlendingMode blendingMode)
    {
        GetRenderAPI()->SetBlendingMode(blendingMode);
    }

    void DrawElements(const std::shared_ptr<VertexArray>& vertexArray, uint32_t elementCount)
    {
        GetRenderAPI()->DrawElements(vertexArray, elementCount);
    }

    void SetDepthTestEnabled(bool bEnabled)
    {
        GetRenderAPI()->SetDepthTestEnabled(bEnabled);
    }

    void InitGraphics(const RenderInitArgs args)
    {
        assert(!g_context);
        g_context = new GraphicsContext();
        g_context->graphicsAPI = args.API;
        g_context->renderAPI = RenderAPI::Create();
        g_context->window = Window::Create(args.WindowSettings);
    }

    void FinishGraphics()
    {
        assert(g_context);
        delete g_context;
        g_context = nullptr;
    }
}