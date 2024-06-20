#pragma once

namespace Nit
{
    class VertexArray;
    class RenderAPI;

    using RenderAPIPtr = std::shared_ptr<RenderAPI>;

    class RenderAPI
    {
    public:
        static RenderAPIPtr Create();

        virtual ~RenderAPI() {};
        virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) const = 0;
        virtual void SetClearColor(const glm::vec4& clearColor) const = 0;
        virtual void Clear() const = 0;
        virtual void SetBlendingEnabled(bool bEnabled) const = 0;
        virtual void SetBlendingMode(const BlendingMode blendingMode) const = 0;
        virtual void DrawElements(const std::shared_ptr<VertexArray>& vertexArray, uint32_t elementCount) const = 0;
        virtual void SetDepthTestEnabled(bool bEnabled) const = 0;
    };
}