#pragma once
#include "VertexObject.h"

namespace Nit::Renderer 
{
    struct RenderInitArgs
    {
    };

    void Init(const RenderInitArgs args = {});
    void Finish();
}