#pragma once

namespace Nit
{
    using ShaderPtr = std::shared_ptr<class Shader>;

    class Shader
    {
    public:
        static ShaderPtr Create();

        virtual void Compile(const char* vertexSource, const char* fragmentSource) = 0;
        
        virtual void SetUniformMat4(const char* uniformName, const glm::mat4& mat) const = 0;
        virtual void SetUniformVec4(const char* uniformName, const glm::vec4& vec) const = 0;
        virtual void SetUniformInt(const char* uniformName, int num) = 0;
        virtual void SetUniformIntArray(const char* uniformName, const int32_t* array, int32_t size) = 0;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;
    };
}