#include "Renderer.h"

namespace Nit::Renderer
{
    struct RendererContext
    {
        GraphicsAPI API = GraphicsAPI::OpenGL;
    };

    RendererContext* ctx = new RendererContext();

    Nit::GraphicsAPI GetGraphicsAPI()
    {
        assert(ctx); return ctx->API;
    }

    void SetGraphicsAPI(GraphicsAPI api)
    {
        assert(ctx); ctx->API = api;
    }
}