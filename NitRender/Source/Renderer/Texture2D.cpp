#include "Texture2D.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture2D.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

namespace Nit
{
    Texture2DPtr Texture2D::Create()
    {
        switch (Renderer::GetGraphicsAPI())
        {
        case GraphicsAPI::OpenGL:
            return std::make_shared<OpenGLTexture2D>();
        case GraphicsAPI::None:
        default:
            return nullptr;
        }
    }

    Image::Image() = default;

    Image::Image(const char* filePath)
    {
        Load(filePath);
    }

    Image::Image(Image&& other) 
        : m_Data(other.m_Data)
        , m_Width(other.m_Width)
        , m_Height(other.m_Height)
        , m_Channels(other.m_Channels)
    {
        other.m_Data = nullptr;
    }

    Image::~Image()
    {
        Free();
    }

    Image& Image::operator=(Image&& other) noexcept
    {
        m_Data     = other.m_Data;
        m_Width    = other.m_Width;
        m_Height   = other.m_Height;
        m_Channels = other.m_Channels;

        other.m_Data = nullptr;
        return *this;
    }

    void Image::Load(const char* filePath)
    {
        if (m_Data)
        {
            Free();
        }

        stbi_set_flip_vertically_on_load(1);
        int width, height, channels;
        m_Data = stbi_load(filePath, &width, &height, &channels, 0);

        if (!m_Data)
        {
            assert(false && "Image not found!");
            return;
        }

        m_Width    = static_cast<uint32_t>(width);
        m_Height   = static_cast<uint32_t>(height);
        m_Channels = static_cast<uint32_t>(channels);
    }

    void Image::Free()
    {
        if (!m_Data)
        {
            return;
        }
        stbi_image_free(m_Data);
        m_Data = nullptr;
    }
}