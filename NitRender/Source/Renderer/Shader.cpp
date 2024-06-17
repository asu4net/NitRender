#include "Shader.h"
#include "RenderAPI.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Nit
{
    ConstantUniquePtr Constant::CreateUnique(const std::string& name, ShaderDataType type, int32_t size)
    {
        return std::make_unique<Constant>(name, type, size);
    }

    Constant::Constant(const std::string& name, ShaderDataType type, int32_t size)
        : m_Data(CreateFromDataType(type))
        , m_Name(name)
        , m_Type(type)
        , m_Size(size)
    {
        if (!m_Data)
        {
            return;
        }
        memset(m_Data, 0, ShaderDataTypeToSize(type));
    }

    Constant::Constant(Constant&& other) noexcept
        : m_Data(other.m_Data)
        , m_Name(other.m_Name)
        , m_Type(other.m_Type)
        , m_Size(other.m_Size)
    {
        other.m_Data = nullptr;
    }

    Constant& Constant::operator=(Constant&& other) noexcept
    {
        m_Data = other.m_Data;
        m_Name = other.m_Name;
        m_Type = other.m_Type;
        m_Size = other.m_Size;
        other.m_Data = nullptr;
        return *this;
    }

    Constant::~Constant()
    {
        if (m_Data)
        {
            delete[] m_Data;
        }
    }

    ShaderPtr Shader::Create()
    {
        switch (GetGraphicsAPI())
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