#include "RenderAPI.h"
#include "Graphics.h"
#include "Platform/OpenGL/OpenGLRenderAPI.h"

namespace Graphics
{
    std::shared_ptr<RenderAPI> RenderAPI::Create()
    {
        switch (GetGraphicsAPI())
        {
        case API::OpenGL:
            return std::make_shared<OpenGLRenderAPI>();
        case API::None:
        default:
            assert(false && "Invalid API");
            return nullptr;
        }
    }
}