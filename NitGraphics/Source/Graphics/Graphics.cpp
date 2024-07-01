#include "Graphics.h"

namespace Graphics
{
    struct GraphicsContext
    {
        API graphicsAPI = API::None;
        std::shared_ptr<RenderAPI> renderAPI = nullptr;
    };
        
    GraphicsContext* g_context = nullptr;

    API GetGraphicsAPI() { assert(g_context); return g_context->graphicsAPI; }
    std::shared_ptr<RenderAPI>  GetRenderAPI()   { assert(g_context); return g_context->renderAPI; }
    
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
        GetRenderAPI()->ClearScreen();
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

    void CreateGraphicsContext(const GraphicsCfg args)
    {
        assert(!g_context);
        g_context = new GraphicsContext();
        g_context->graphicsAPI = args.graphicsAPI;
        g_context->renderAPI = RenderAPI::Create();
    }

    void DestroyGraphicsContext()
    {
        assert(g_context);
        delete g_context;
        g_context = nullptr;
    }
}