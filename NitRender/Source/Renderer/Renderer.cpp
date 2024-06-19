#include "Renderer.h"
#include "RenderAPI.h"

namespace Nit::Renderer
{
    struct RendererContext
    {
        GraphicsAPI  graphicsAPI = GraphicsAPI::None;
        RenderAPIPtr renderAPI   = nullptr;
    };

    RendererContext* ctx = nullptr;
    
    GraphicsAPI GetGraphicsAPI() { assert(ctx); return ctx->graphicsAPI; }
    RenderAPIPtr GetRenderAPI()  { assert(ctx); return ctx->renderAPI; }
    
    void Init(const RenderInitArgs args)
    {
        if (ctx)
        {
            assert(false);
            return;
        }

        ctx = new RendererContext();
        ctx->graphicsAPI = args.graphicsAPI;
        ctx->renderAPI   = RenderAPI::Create();
    }
    
    void Finish()
    {
        if (ctx)
        {
            delete ctx;
            ctx = nullptr;
        }
    }
}