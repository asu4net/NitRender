#include "RenderingContext.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLRenderingContext.h"

namespace Nit
{
    std::unique_ptr<RenderingContext> RenderingContext::Create(void* windowHandler)
    {
        switch (Renderer::GetGraphicsAPI())
        {
        case GraphicsAPI::OpenGL:
            return std::make_unique<OpenGLRenderingContext>(windowHandler);
        case GraphicsAPI::None:
        default:
            assert(false && "Invalid API");
            return nullptr;
        }
    }
}