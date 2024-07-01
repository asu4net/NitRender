#include "RenderingContext.h"
#include "Graphics.h"
#include "Platform/OpenGL/OpenGLRenderingContext.h"

namespace Graphics
{
    std::unique_ptr<RenderingContext> RenderingContext::Create(void* windowHandler)
    {
        switch (GetGraphicsAPI())
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