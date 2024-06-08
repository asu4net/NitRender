#include "Shader.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Nit
{
    ShaderPtr Shader::Create()
    {
        switch (Renderer::GetGraphicsAPI())
        {
        case GraphicsAPI::OpenGL:
            return std::make_shared<OpenGLShader>();
        case GraphicsAPI::None:
        default:
            assert(false && "Invalid API");
            return nullptr;
        }
    }
}