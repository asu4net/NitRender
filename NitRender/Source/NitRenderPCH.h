#pragma once

#include <iostream>
#include <stdint.h>
#include <string>
#include <vector>
#include <memory>
#include <assert.h>
#include <unordered_map>
#include <functional>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

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
}