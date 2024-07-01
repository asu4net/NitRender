#include "Material.h"
#include "Shader.h"
#include "Texture2D.h"

namespace Graphics
{
    Material::Material(const std::shared_ptr<Shader>& shader, const std::shared_ptr<Texture2D>& texture)
        : m_shader(shader)
        , m_texture(texture)
    {
        if (!m_shader)
        {
            assert(false && "A valid shader pointer is required!");
            return;
        }

        std::vector<std::unique_ptr<Constant>> shaderConstants;
        m_shader->GetConstantCollection(shaderConstants);
        const size_t numOfConstants = shaderConstants.size();
        m_usedConstants.reserve(numOfConstants);

        for (size_t i = 0; i < numOfConstants; ++i)
        {
            const std::string constantName = shaderConstants[i]->GetName();
            m_constants[constantName] = std::move(shaderConstants[i]);
        }
    }

    void Material::SetConstantFloat(const std::string& name, float value)
    {
        Constant* constant = GetConstant(name);
        *constant->GetFloatData() = value;
        m_usedConstants[name] = constant;
    }

    void Material::SetConstantVec2(const std::string& name, const glm::vec2& value)
    {
        Constant* constant = GetConstant(name);
        float* floatData = constant->GetFloatData();
        floatData[0] = value.x; floatData[1] = value.y;
        m_usedConstants[name] = constant;
    }

    void Material::SetConstantVec3(const std::string& name, const glm::vec3& value)
    {
        Constant* constant = GetConstant(name);
        float* floatData = constant->GetFloatData();
        floatData[0] = value.x; floatData[1] = value.y; floatData[2] = value.z;
        m_usedConstants[name] = constant;
    }

    void Material::SetConstantVec4(const std::string& name, const glm::vec4& value)
    {
        Constant* constant = GetConstant(name);
        float* floatData = constant->GetFloatData();
        floatData[0] = value.x; floatData[1] = value.y; floatData[2] = value.z; floatData[3] = value.w;
        m_usedConstants[name] = constant;
    }

    void Material::SetConstantMat4(const std::string& name, const glm::mat4& value)
    {
        Constant* constant = GetConstant(name);
        float* floatData = constant->GetFloatData();
        const float* matrixData = glm::value_ptr(value);

        for (int i = 0; i < 16; ++i)
        {
            floatData[i] = matrixData[i];
        }

        m_usedConstants[name] = constant;
    }

    void Material::SetConstantInt(const std::string& name, int32_t value)
    {
        Constant* constant = GetConstant(name);
        *constant->GetIntData() = value;
        m_usedConstants[name] = constant;
    }

    void Material::SetConstantSampler2D(const std::string& name, const int32_t* value, int32_t size)
    {
        Constant* constant = GetConstant(name);
        int32_t* floatData = constant->GetIntData();

        for (int32_t i = 0; i < size; ++i)
        {
            floatData[i] = value[i];
        }

        m_usedConstants[name] = constant;
    }

    void Material::SubmitConstants()
    {
        m_shader->Bind();

        for (auto& [key, constant] : m_usedConstants)
        {
            if (!constant)
                break;

            const char* constantName = constant->GetName().c_str();
            ShaderDataType constantType = constant->GetType();
            int32_t* intData = constant->GetIntData();
            float* floatData = constant->GetFloatData();

            switch (constantType)
            {
            default:
            case ShaderDataType::None:
            case ShaderDataType::Int2:
            case ShaderDataType::Int3:
            case ShaderDataType::Int4:
            case ShaderDataType::Mat3:
                assert(false && "Unsupported type!");
                break;

            case ShaderDataType::Int:
                m_shader->SetConstantInt(constantName, *intData);
                break;
            case ShaderDataType::Sampler2D:
                m_shader->SetConstantSampler2D(constantName, intData, ShaderDataTypeToSize(constantType));
                break;
            case ShaderDataType::Float:
                m_shader->SetConstantFloat(constantName, *floatData);
                break;
            case ShaderDataType::Float2:
                m_shader->SetConstantVec2(constantName, floatData);
                break;
            case ShaderDataType::Float3:
                m_shader->SetConstantVec3(constantName, floatData);
                break;
            case ShaderDataType::Float4:
                m_shader->SetConstantVec4(constantName, floatData);
                break;
            case ShaderDataType::Mat4:
                m_shader->SetConstantMat4(constantName, floatData);
                break;
            case ShaderDataType::Bool:
                break;
            }
        }

        m_usedConstants.clear();
    }

    Constant* Material::GetConstant(const std::string& name)
    {
        if (m_constants.count(name))
        {
            return m_constants[name].get();
        }

        assert(false && "Constant does not exist!");
        return nullptr;
    }
}