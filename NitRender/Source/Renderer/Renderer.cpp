#include "Renderer.h"
#include "RenderAPI.h"

namespace Nit::Renderer
{
    struct RendererContext
    {
        RenderAPIPtr API = nullptr;
    };

    RendererContext* ctx = nullptr;
    
    void Init(const RenderInitArgs args)
    {
        if (ctx)
        {
            assert(false);
            return;
        }

        ctx = new RendererContext();
        ctx->API = RenderAPI::Create();
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