#include "RenderAPI.h"
#include "Graphics.h"
#include "Platform/OpenGL/OpenGLRenderAPI.h"

namespace Nit
{
    RenderAPIPtr RenderAPI::Create()
    {
        switch (GetGraphicsAPI())
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