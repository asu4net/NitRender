#include "RenderingContext.h"
#include "Graphics.h"
#include "Platform/OpenGL/OpenGLRenderingContext.h"

namespace Graphics
{
    std::unique_ptr<RenderingContext> RenderingContext::Create(void* windowHandler)
    {
        switch (GetGraphicsAPI())
        {
        case API::OpenGL:
            return std::make_unique<OpenGLRenderingContext>(windowHandler);
        case API::None:
        default:
            assert(false && "Invalid API");
            return nullptr;
        }
    }
}