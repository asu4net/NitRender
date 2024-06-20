#include "Renderer2D.h"
#include "RenderAPI.h"

namespace Nit::Renderer2D
{
    struct RendererContext
    {
    };

    RendererContext* ctx = nullptr;

    void InitRender2D(const Render2DInitArgs args)
    {
        if (ctx)
        {
            assert(false);
            return;
        }

        ctx = new RendererContext();
    }

    void FinishRender2D()
    {
        if (ctx)
        {
            delete ctx;
            ctx = nullptr;
        }
    }
}