#pragma once
#include "Graphics/Texture2D.h"

namespace Graphics
{
    class OpenGLTexture2D : public Texture2D
    {
    public:
        OpenGLTexture2D();
        ~OpenGLTexture2D();
        
        void UploadToGPU(const void* data, uint32_t Width, uint32_t Height, uint32_t Channels, const Texture2DSettings& settings = {}) override;
        void UploadToGPU(const Image& image, const Texture2DSettings& settings = {}) override;
        uint32_t GetTextureID() const override { return m_textureID; }
        void Bind(uint32_t slot = 0) const override;

    private:
        uint32_t m_textureID = 0;
        bool m_uploaded = false;
    };
}