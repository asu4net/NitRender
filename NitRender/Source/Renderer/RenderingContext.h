#pragma once

namespace Nit
{
    class RenderingContext
    {
    public:
        static std::unique_ptr<RenderingContext> Create(void* windowHandler);

        virtual void SwapBuffers() const = 0;
    };
}