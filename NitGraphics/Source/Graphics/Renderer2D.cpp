#include "Renderer2D.h"
#include "RenderAPI.h"

namespace Nit::Renderer2D
{
    struct RendererContext
    {
        RenderAPIPtr API = nullptr;
    };

    RendererContext* ctx = nullptr;

    void Init(const Render2DInitArgs args)
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