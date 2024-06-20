#pragma once


namespace Nit
{
    struct Render2DInitArgs
    {
    };
}

namespace Nit::Renderer2D
{
    void InitRender2D(const Render2DInitArgs args = {});
    void FinishRender2D();
}