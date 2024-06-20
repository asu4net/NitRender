#pragma once
#include "VertexObject.h"
#include "RenderAPI.h"

namespace Nit 
{
    struct RenderInitArgs
    {
        GraphicsAPI graphicsAPI = GraphicsAPI::OpenGL;
    };
    
    GraphicsAPI  GetGraphicsAPI ();
    RenderAPIPtr GetRenderAPI   ();

    void InitGraphics(const RenderInitArgs args = {});
    
    void FinishGraphics();
}