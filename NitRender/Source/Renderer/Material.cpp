#include "Material.h"

namespace Nit
{
    Material::Material(const ShaderPtr& shader, const Texture2DPtr& texture)
        : m_Shader(shader)
        , m_Texture(texture)
    {
        if (!m_Shader)
        {
            assert(false && "A valid shader pointer is required!");
            return;
        }

        std::vector<ConstantUniquePtr> shaderConstants;
        m_Shader->GetConstantCollection(shaderConstants);
        const size_t numOfConstants = shaderConstants.size();
        m_UsedConstants.reserve(numOfConstants);

        for (size_t i = 0; i < numOfConstants; ++i)
        {
            const std::string constantName = shaderConstants[i]->GetName();
            m_Constants[constantName] = std::move(shaderConstants[i]);
        }
    }
    
    void Material::SetConstantFloat(const std::string& name, float value)
    {
        Constant* constant = m_Constants[name].get();
        *constant->GetFloatData() = value;
        m_UsedConstants[name] = constant;
    }

    void Material::SetConstantVec2(const std::string& name, const glm::vec2& value)
    {
        Constant* constant = m_Constants[name].get();
        float* floatData = constant->GetFloatData();
        floatData[0] = value.x; floatData[1] = value.y;
        m_UsedConstants[name] = constant;
    }

    void Material::SetConstantVec3(const std::string& name, const glm::vec3& value)
    {
        Constant* constant = m_Constants[name].get();
        float* floatData = constant->GetFloatData();
        floatData[0] = value.x; floatData[1] = value.y; floatData[2] = value.z;
        m_UsedConstants[name] = constant;
    }

    void Material::SetConstantVec4(const std::string& name, const glm::vec4& value)
    {
        Constant* constant = m_Constants[name].get();
        float* floatData = constant->GetFloatData();
        floatData[0] = value.x; floatData[1] = value.y; floatData[2] = value.z; floatData[3] = value.w;
        m_UsedConstants[name] = constant;
    }

    void Material::SetConstantMat4(const std::string& name, const glm::mat4& value)
    {
        Constant* constant = m_Constants[name].get();
        float* floatData = constant->GetFloatData();
        const float* matrixData = glm::value_ptr(value);
        
        for (int i = 0; i < 16; ++i)
        {
            floatData[i] = matrixData[i];
        }

        m_UsedConstants[name] = constant;
    }

    void Material::SetConstantInt(const std::string& name, int32_t value)
    {
        Constant* constant = m_Constants[name].get();
        *constant->GetIntData() = value;
        m_UsedConstants[name] = constant;
    }

    void Material::SetConstantSampler2D(const std::string& name, const int32_t* value, int32_t size)
    {
        Constant* constant = m_Constants[name].get();
        int32_t* floatData = constant->GetIntData();

        for (uint32_t i = 0; i < size; ++i)
        {
            floatData[i] = value[i];
        }

        m_UsedConstants[name] = constant;
    }

    void Material::SubmitConstants()
    {
        m_Shader->Bind();

        for (auto& [key, constant] : m_UsedConstants)
        {
            if (!constant)
                break;

            const char*    constantName = constant->GetName().c_str();
            ShaderDataType constantType = constant->GetType();
            int32_t*       intData      = constant->GetIntData();
            float*         floatData    = constant->GetFloatData();
            
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
                m_Shader->SetConstantInt(constantName, *intData);
                break;
            case ShaderDataType::Sampler2D:
                m_Shader->SetConstantSampler2D(constantName, intData, ShaderDataTypeToSize(constantType));
                break;
            case ShaderDataType::Float:
                m_Shader->SetConstantFloat(constantName, *floatData);
                break;
            case ShaderDataType::Float2:
                m_Shader->SetConstantVec2(constantName, floatData);
                break;
            case ShaderDataType::Float3:
                m_Shader->SetConstantVec3(constantName, floatData);
                break;
            case ShaderDataType::Float4:
                m_Shader->SetConstantVec4(constantName, floatData);
                break;
            case ShaderDataType::Mat4:
                m_Shader->SetConstantMat4(constantName, floatData);
                break;
            case ShaderDataType::Bool:
                break;
            }
        }

        m_UsedConstants.clear();
    }
}