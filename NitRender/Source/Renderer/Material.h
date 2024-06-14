#pragma once
#include "Shader.h"
#include "Texture2D.h"

namespace Nit
{
    class Material
    {
    public:
        Material(const ShaderPtr& shader, const Texture2DPtr& texture);
        ~Material();

    private:
        ShaderPtr                      m_Shader    = nullptr;
        Texture2DPtr                   m_Texture   = nullptr;
        std::vector<ConstantUniquePtr> m_Constants;
    };
}