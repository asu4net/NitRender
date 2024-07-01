#include "VertexObject.h"
#include "Graphics.h"
#include "Platform/OpenGL/OpenGLVertexObject.h"

namespace Graphics
{
    std::shared_ptr<VertexBuffer> VertexBuffer::Create(const void* vertices, uint32_t size)
    {
        switch (GetGraphicsAPI())
        {
        case API::OpenGL:
            return std::make_shared<OpenGLVertexBuffer>(vertices, size);
        case API::None:
        default:
            assert(false);
            return nullptr;
        }
    }

    std::shared_ptr<VertexBuffer> VertexBuffer::Create(uint32_t size)
    {
        switch (GetGraphicsAPI())
        {
        case API::OpenGL:
            return std::make_shared<OpenGLVertexBuffer>(size);
        case API::None:
        default:
            assert(false);
            return nullptr;
        }
    }

    std::shared_ptr<IndexBuffer> IndexBuffer::Create(const uint32_t* indices, uint32_t count)
    {
        switch (GetGraphicsAPI())
        {
        case API::OpenGL:
            return std::make_shared<OpenGLIndexBuffer>(indices, count);
        case API::None:
        default:
            assert(false);
            return nullptr;
        }
    }

    std::shared_ptr<VertexArray> VertexArray::Create()
    {
        switch (GetGraphicsAPI())
        {
        case API::OpenGL:
            return std::make_shared<OpenGLVertexArray>();
        case API::None:
        default:
            assert(false);
            return nullptr;
        }
    }
}