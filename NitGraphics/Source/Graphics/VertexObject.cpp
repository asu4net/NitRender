#include "VertexObject.h"
#include "Graphics.h"
#include "Platform/OpenGL/OpenGLVertexObject.h"

namespace Graphics
{
    VertexBufferSPtr VertexBuffer::Create(const void* vertices, uint32_t size)
    {
        switch (GetGraphicsAPI())
        {
        case GraphicsAPI::OpenGL:
            return std::make_shared<OpenGLVertexBuffer>(vertices, size);
        case GraphicsAPI::None:
        default:
            assert(false);
            return nullptr;
        }
    }

    VertexBufferSPtr VertexBuffer::Create(uint32_t size)
    {
        switch (GetGraphicsAPI())
        {
        case GraphicsAPI::OpenGL:
            return std::make_shared<OpenGLVertexBuffer>(size);
        case GraphicsAPI::None:
        default:
            assert(false);
            return nullptr;
        }
    }

    IndexBufferSPtr IndexBuffer::Create(const uint32_t* indices, uint32_t count)
    {
        switch (GetGraphicsAPI())
        {
        case GraphicsAPI::OpenGL:
            return std::make_shared<OpenGLIndexBuffer>(indices, count);
        case GraphicsAPI::None:
        default:
            assert(false);
            return nullptr;
        }
    }

    VertexArraySPtr VertexArray::Create()
    {
        switch (GetGraphicsAPI())
        {
        case GraphicsAPI::OpenGL:
            return std::make_shared<OpenGLVertexArray>();
        case GraphicsAPI::None:
        default:
            assert(false);
            return nullptr;
        }
    }
}