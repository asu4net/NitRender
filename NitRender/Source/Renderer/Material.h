#pragma once
#include "Shader.h"
#include "Texture2D.h"

namespace Nit
{
    class Material
    {
    public:
        using ConstantMap     = std::unordered_map<std::string, std::unique_ptr<Constant>>;
        using UsedConstantMap = std::unordered_map<std::string, Constant*>;

        Material(const ShaderPtr& shader, const Texture2DPtr& texture = {});
        ~Material() = default;

        const ShaderPtr&    GetShader()  const { return m_Shader; }
        const Texture2DPtr& GetTexture() const { return m_Texture; }

        //#TODO_asuarez Add getters in order to retrieve the constant values.... check if value changed!!

        void SetConstantFloat     (const std::string& name, float value);
        void SetConstantVec2      (const std::string& name, const glm::vec2& value);
        void SetConstantVec3      (const std::string& name, const glm::vec3& value);
        void SetConstantVec4      (const std::string& name, const glm::vec4& value);
        void SetConstantMat4      (const std::string& name, const glm::mat4& value);
        void SetConstantInt       (const std::string& name, int32_t value);
        void SetConstantSampler2D (const std::string& name, const int32_t* value, int32_t size);

        void SubmitConstants();

    private:
        ShaderPtr              m_Shader           = nullptr;
        Texture2DPtr           m_Texture          = nullptr;
        ConstantMap            m_Constants;
        UsedConstantMap        m_UsedConstants;
    };
}