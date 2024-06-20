#pragma once


namespace Nit
{
    struct Render2DInitArgs
    {
    };
}

namespace Nit::Renderer2D
{
    void Init(const Render2DInitArgs args = {});
    void Finish();
}