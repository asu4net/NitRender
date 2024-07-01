#pragma once
#include "Graphics/Shader.h"

namespace Graphics
{
    class OpenGLShader : public Shader
    {
    public:
        OpenGLShader();
        ~OpenGLShader();

        void Compile(const char* vertexSource, const char* fragmentSource) override;

        void GetConstantCollection(std::vector<std::unique_ptr<Constant>>& constants) const override;

        void SetConstantFloat     (const char* name, float value)                        const override;
        void SetConstantVec2      (const char* name, const float* value)                 const override;
        void SetConstantVec3      (const char* name, const float* value)                 const override;
        void SetConstantVec4      (const char* name, const float* value)                 const override;
        void SetConstantMat4      (const char* name, const float* value)                 const override;
        void SetConstantInt       (const char* name, int value)                          const override;
        void SetConstantSampler2D (const char* name, const int32_t* value, int32_t size) const override;

        void Bind()   const override;
        void Unbind() const override;

    private:        
        uint32_t   m_shaderId  = 0;
        bool       m_bCompiled  = false;
    };
}