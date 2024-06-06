#pragma once
#include "VertexObject.h"

namespace Nit::Renderer 
{
    GraphicsAPI GetGraphicsAPI();
    void SetGraphicsAPI(GraphicsAPI api);

    struct RenderInitArgs
    {
        GraphicsAPI API = GraphicsAPI::OpenGL;
    };
}