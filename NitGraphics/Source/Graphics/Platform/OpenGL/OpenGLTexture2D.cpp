#include "OpenGLTexture2D.h"
#include <GLAD/glad.h>

namespace Graphics
{
    void SetMagFilter(const uint32_t textureId, const MagnificationFilter magFilter)
    {
        switch (magFilter)
        {
        case MagnificationFilter::Linear:
            glTextureParameteri(textureId, GL_TEXTURE_MAG_FILTER, GL_LINEAR); return;
        case MagnificationFilter::Nearest:
            glTextureParameteri(textureId, GL_TEXTURE_MAG_FILTER, GL_NEAREST); return;
        }
    }

    void SetMinFilter(const uint32_t textureId, const MinificationFilter magFilter)
    {
        switch (magFilter)
        {
        case MinificationFilter::Linear:
            glTextureParameteri(textureId, GL_TEXTURE_MIN_FILTER, GL_LINEAR); return;
        case MinificationFilter::Nearest:
            glTextureParameteri(textureId, GL_TEXTURE_MIN_FILTER, GL_NEAREST); return;
        }
    }

    void SetWrapMode(const uint32_t textureId, const TextureCoordinate textureCoordinate, const TextureWrapMode wrapMode)
    {
        const GLenum coord = textureCoordinate == TextureCoordinate::U ? GL_TEXTURE_WRAP_S : GL_TEXTURE_WRAP_T;

        switch (wrapMode)
        {
        case TextureWrapMode::Repeat:
            glTextureParameteri(textureId, coord, GL_REPEAT); return;
        case TextureWrapMode::ClampToEdge:
            glTextureParameteri(textureId, coord, GL_CLAMP_TO_EDGE); return;
        }
    }

    OpenGLTexture2D::OpenGLTexture2D() = default;

    OpenGLTexture2D::~OpenGLTexture2D()
    {
        glDeleteTextures(1, &m_textureID);
    }

    void OpenGLTexture2D::UploadToGPU(const void* data, uint32_t Width, uint32_t Height, uint32_t Channels, const Texture2DSettings& settings)
    {
        assert(data && "Missing texture data!");
        assert(Width && Height && "Invalid width or height!");

        if (m_uploaded)
        {
            glDeleteTextures(1, &m_textureID);
            m_uploaded = false;
        }

        GLenum internalFormat = 0, dataFormat = 0;

        if (Channels == 4)
        {
            internalFormat = GL_RGBA8;
            dataFormat = GL_RGBA;
        }
        else if (Channels == 3)
        {
            internalFormat = GL_RGB8;
            dataFormat = GL_RGB;
        }

        glCreateTextures(GL_TEXTURE_2D, 1, &m_textureID);
        glTextureStorage2D(m_textureID, 1, internalFormat, Width, Height);

        SetMinFilter(m_textureID, settings.MinFilter);
        SetMagFilter(m_textureID, settings.MagFilter);

        SetWrapMode(m_textureID, TextureCoordinate::U, settings.WrapModeU);
        SetWrapMode(m_textureID, TextureCoordinate::V, settings.WrapModeV);

        glTextureSubImage2D(m_textureID, 0, 0, 0, Width, Height,
            dataFormat, GL_UNSIGNED_BYTE, data);

        m_uploaded = true;
    }

    void OpenGLTexture2D::UploadToGPU(const Image& image, const Texture2DSettings& settings)
    {
        void* data = image.GetData();
        if (!data)
        {
            assert(false && "Image is not loaded!");
            return;
        }

        UploadToGPU(image.GetData(), image.GetWidth(), image.GetHeight(), image.GetChannels(), settings);
    }

    void OpenGLTexture2D::Bind(const uint32_t slot) const
    {
        glBindTextureUnit(slot, m_textureID);
    }
}