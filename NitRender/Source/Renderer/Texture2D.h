#pragma once

namespace Nit
{
    struct Texture2DSettings
    {
        uint32_t            Width     = 0;
        uint32_t            Height    = 0;
        uint32_t            Channels  = 0;
        MagnificationFilter MagFilter = MagnificationFilter::Linear;
        MinificationFilter  MinFilter = MinificationFilter::Linear;
        TextureWrapMode     WrapModeU = TextureWrapMode::Repeat;
        TextureWrapMode     WrapModeV = TextureWrapMode::Repeat;
    };

    using Texture2DPtr = std::shared_ptr<class Texture2D>;

    class Texture2D
    {
    public:
        static Texture2DPtr  Create();
        virtual void         UploadToGPU(const Texture2DSettings& settings, const void* data) = 0;
        virtual uint32_t     GetTextureID() const = 0;
        virtual void         Bind(uint32_t slot = 0) const = 0;
    };

    class Image
    {
    public:
        Image();
        Image(const char* filePath);
        Image(const Image& other) = delete;
        Image(Image&& other);
        ~Image();

        Image& operator=(const Image& other) = delete;
        Image& operator=(Image&& other) noexcept;

        uint32_t GetWidth()    const { return m_Width; }
        uint32_t GetHeight()   const { return m_Height; }
        uint32_t GetChannels() const { return m_Channels; }

        void Load(const char* filePath);
        void Free();

        unsigned char* GetData() const { return m_Data; };

    private:
        unsigned char* m_Data = nullptr;
        uint32_t       m_Width     = 0;
        uint32_t       m_Height    = 0;
        uint32_t       m_Channels  = 0;
    };
}