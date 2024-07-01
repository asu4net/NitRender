#pragma once

namespace Graphics
{
    class Shader;
    class Texture2D;

    class Material
    {
    public:
        using ConstantMap     = std::unordered_map<std::string, std::unique_ptr<class Constant>>;
        using UsedConstantMap = std::unordered_map<std::string, Constant*>;

        Material(const std::shared_ptr<Shader>& shader, const std::shared_ptr<Texture2D>& texture = {});
        ~Material() = default;

        const std::shared_ptr<Shader>& GetShader()  const { return m_shader; }
        const std::shared_ptr<Texture2D>& GetTexture() const { return m_texture; }

        //#TODO_asuarez Add getters in order to retrieve the constant values.... check if value changed!!

        void SetConstantFloat(const std::string& name, float value);
        void SetConstantVec2(const std::string& name, const glm::vec2& value);
        void SetConstantVec3(const std::string& name, const glm::vec3& value);
        void SetConstantVec4(const std::string& name, const glm::vec4& value);
        void SetConstantMat4(const std::string& name, const glm::mat4& value);
        void SetConstantInt(const std::string& name, int32_t value);
        void SetConstantSampler2D(const std::string& name, const int32_t* value, int32_t size);

        void SubmitConstants();

    private:
        Constant* GetConstant(const std::string& name);

        std::shared_ptr<Shader>    m_shader         = nullptr;
        std::shared_ptr<Texture2D> m_texture        = nullptr;
        ConstantMap                m_constants;
        UsedConstantMap            m_usedConstants;
    };
}