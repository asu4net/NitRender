#pragma once
#include "Renderer/Shader.h"

namespace Nit
{
    class OpenGLShader : public Shader
    {
    public:
        OpenGLShader();
        ~OpenGLShader();

        void Compile(const char* vertexSource, const char* fragmentSource) override;

        void GetConstantCollection(std::vector<ConstantUniquePtr>& constants) const override;
        void SetConstantMat4(const char* constantName, const glm::mat4& mat) const override;
        void SetConstantVec4(const char* constantName, const glm::vec4& vec) const override;
        void SetConstantInt(const char* constantName, int num) override;
        void SetConstantIntArray(const char* constantName, const int32_t* array, int32_t size) override;

        void Bind() const override;
        void Unbind() const override;

    private:
        
        ShaderPtr m_SharedPtr = nullptr;
        uint32_t  m_ShaderId   = 0;
        bool      m_Compiled       = false;
    };
}