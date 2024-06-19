#pragma once
#include "VertexObject.h"
#include "RenderAPI.h"

namespace Nit::Renderer 
{
    struct RenderInitArgs
    {
        GraphicsAPI graphicsAPI = GraphicsAPI::OpenGL;
    };
    
    GraphicsAPI  GetGraphicsAPI();
    RenderAPIPtr GetRenderAPI();

    void Init(const RenderInitArgs args = {});
    
    void Finish();
}