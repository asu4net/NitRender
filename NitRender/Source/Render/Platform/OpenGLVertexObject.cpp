#include "OpenGLVertexObject.h"
#include <glad/glad.h>
#include <stdint.h>
#include <cassert>

namespace Nit
{
    OpenGLVertexBuffer::OpenGLVertexBuffer(const void* vertices, const uint32_t size)
        : m_BufferId(0)
    {
        glCreateBuffers(1, &m_BufferId);
        glBindBuffer(GL_ARRAY_BUFFER, m_BufferId);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

    OpenGLVertexBuffer::OpenGLVertexBuffer(const uint32_t size)
    {
        glCreateBuffers(1, &m_BufferId);
        glBindBuffer(GL_ARRAY_BUFFER, m_BufferId);
        glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer()
    {
        glDeleteBuffers(1, &m_BufferId);
    }

    void OpenGLVertexBuffer::Bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_BufferId);
    }

    void OpenGLVertexBuffer::Unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void OpenGLVertexBuffer::SetData(const void* data, const uint32_t size) const
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_BufferId);
        glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
    }

    void OpenGLVertexBuffer::SetLayout(const BufferLayout& bufferLayout)
    {
        m_Layout = bufferLayout;
    }

    OpenGLIndexBuffer::OpenGLIndexBuffer(const uint32_t* indices, const uint32_t count)
        : m_BufferId(0)
        , m_Count(count)
    {
        glCreateBuffers(1, &m_BufferId);
        Bind();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer()
    {
        glDeleteBuffers(1, &m_BufferId);
    }

    void OpenGLIndexBuffer::Bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferId);
    }

    void OpenGLIndexBuffer::Unbind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    static GLenum ShaderDataTypeToOpenGlBaseType(const ShaderDataType type)
    {
        switch (type)
        {
        case ShaderDataType::None:   return 0;
        case ShaderDataType::Float:  return GL_FLOAT;
        case ShaderDataType::Float2: return GL_FLOAT;
        case ShaderDataType::Float3: return GL_FLOAT;
        case ShaderDataType::Float4: return GL_FLOAT;
        case ShaderDataType::Mat3:   return GL_FLOAT;
        case ShaderDataType::Mat4:   return GL_FLOAT;
        case ShaderDataType::Int:    return GL_INT;
        case ShaderDataType::Int2:   return GL_INT;
        case ShaderDataType::Int3:   return GL_INT;
        case ShaderDataType::Int4:   return GL_INT;
        case ShaderDataType::Bool:   return GL_BOOL;
        default:                     return 0;
        }
    }

    OpenGLVertexArray::OpenGLVertexArray()
        : m_VertexArrayId(0)
    {
        glCreateVertexArrays(1, &m_VertexArrayId);
    }

    OpenGLVertexArray::~OpenGLVertexArray()
    {
        glDeleteVertexArrays(1, &m_VertexArrayId);
    }

    void OpenGLVertexArray::Bind() const
    {
        glBindVertexArray(m_VertexArrayId);
    }

    void OpenGLVertexArray::Unbind() const
    {
        glBindVertexArray(0);
    }

    void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
    {
        assert(!vertexBuffer->GetLayout().GetElements().empty() && "Vertex buffer has no layout!");

        glBindVertexArray(m_VertexArrayId);
        vertexBuffer->Bind();
        uint32_t index = 0;
        const BufferLayout& bufferLayout = vertexBuffer->GetLayout();
        for (const auto& element : bufferLayout)
        {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(
                index,
                element.GetComponentCount(),
                ShaderDataTypeToOpenGlBaseType(element.Type),
                element.Normalized ? GL_TRUE : GL_FALSE,
                bufferLayout.GetStride(),
                reinterpret_cast<void*>(static_cast<intptr_t>(element.Offset))
            );
            index++;
        }
        m_VertexBuffers.push_back(vertexBuffer);
    }

    void OpenGLVertexArray::SetIndexBuffer(const  std::shared_ptr<IndexBuffer>& indexBuffer)
    {
        glBindVertexArray(m_VertexArrayId);
        indexBuffer->Bind();
        m_IndexBuffer = indexBuffer;
    }
}