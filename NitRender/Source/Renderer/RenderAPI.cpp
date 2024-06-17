#include "RenderAPI.h"
#include "Platform/OpenGL/OpenGLRenderAPI.h"

namespace Nit
{
    GraphicsAPI API = GraphicsAPI::OpenGL;
    GraphicsAPI GetGraphicsAPI() { return API; }

    void SetGraphicsAPI(GraphicsAPI api) { API = api; }

    RenderAPIPtr RenderAPI::Create()
    {
        switch (API)
        {
        case GraphicsAPI::OpenGL:
            return std::make_shared<OpenGLRenderAPI>();
        case GraphicsAPI::None:
        default:
            assert(false && "Invalid API");
            return nullptr;
        }
    }
}