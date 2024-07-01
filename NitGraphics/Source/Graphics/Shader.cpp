#include "Shader.h"
#include "Graphics.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Graphics
{
    std::unique_ptr<Constant> Constant::CreateUnique(const std::string& name, ShaderDataType type, int32_t size)
    {
        return std::make_unique<Constant>(name, type, size);
    }

    Constant::Constant(const std::string& name, ShaderDataType type, int32_t size)
        : m_data(CreateFromDataType(type))
        , m_name(name)
        , m_type(type)
        , m_size(size)
    {
        if (!m_data)
        {
            return;
        }
        memset(m_data, 0, ShaderDataTypeToSize(type));
    }

    Constant::Constant(Constant&& other) noexcept
        : m_data(other.m_data)
        , m_name(other.m_name)
        , m_type(other.m_type)
        , m_size(other.m_size)
    {
        other.m_data = nullptr;
    }

    Constant& Constant::operator=(Constant&& other) noexcept
    {
        m_data = other.m_data;
        m_name = other.m_name;
        m_type = other.m_type;
        m_size = other.m_size;
        other.m_data = nullptr;
        return *this;
    }

    Constant::~Constant()
    {
        if (m_data)
        {
            delete[] m_data;
        }
    }

    std::shared_ptr<Shader> Shader::Create()
    {
        switch (GetGraphicsAPI())
        {
        case API::OpenGL:
            return std::make_shared<OpenGLShader>();
        case API::None:
        default:
            assert(false && "Invalid API");
            return nullptr;
        }
    }
}