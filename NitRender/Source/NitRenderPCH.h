#pragma once

#include <iostream>
#include <stdint.h>
#include <string>
#include <vector>
#include <memory>
#include <assert.h>
#include <unordered_map>
#include <functional>
#include <cassert>
#include <array>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace Nit
{
    enum class BlendingMode
    {
        Alpha,
        Solid,
        Add,
        Multiply
    };

    enum class GraphicsAPI
    {
        None, OpenGL
    };

    enum class MinificationFilter 
    { 
        Linear, Nearest 
    };

    enum class MagnificationFilter 
    { 
        Linear, Nearest 
    };
    
    enum class TextureWrapMode 
    { 
        Repeat, ClampToEdge 
    };
    
    enum class TextureCoordinate 
    { 
        U, V 
    };
}