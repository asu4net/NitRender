#include "RenderAPI.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLRenderAPI.h"

namespace Nit
{
    RenderAPIPtr RenderAPI::Create()
    {
        switch (Renderer::GetGraphicsAPI())
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