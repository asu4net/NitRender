#include "RenderAPI.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLRenderAPI.h"

namespace Nit
{
    std::shared_ptr<RenderAPI> RenderAPI::Create()
    {
        switch (Renderer::GetGraphicsAPI())
        {
        case GraphicsAPI::OpenGL:
            return std::shared_ptr<OpenGLRenderAPI>();
        case GraphicsAPI::None:
        default:
            assert(false && "Invalid API");
            return nullptr;
        }
    }
}