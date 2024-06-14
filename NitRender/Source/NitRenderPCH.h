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

    enum class ShaderDataType
    {
        None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
    };

    inline static uint32_t ShaderDataTypeToSize(const ShaderDataType type)
    {
        switch (type)
        {
        case ShaderDataType::Float:     return 4;
        case ShaderDataType::Float2:    return 4 * 2;
        case ShaderDataType::Float3:    return 4 * 3;
        case ShaderDataType::Float4:    return 4 * 4;
        case ShaderDataType::Mat3:      return 4 * 3 * 3;
        case ShaderDataType::Mat4:      return 4 * 4 * 4;
        case ShaderDataType::Int:       return 4;
        case ShaderDataType::Int2:      return 4 * 2;
        case ShaderDataType::Int3:      return 4 * 3;
        case ShaderDataType::Int4:      return 4 * 4;
        case ShaderDataType::Bool:      return 1;
        case ShaderDataType::None:
        default:                        return 0;
        }
    }

    inline static void* CreateFromDataType(const ShaderDataType type)
    {
        switch (type)
        {
        case ShaderDataType::Float:     return new float;
        case ShaderDataType::Float2:    return new float[2];
        case ShaderDataType::Float3:    return new float[3];
        case ShaderDataType::Float4:    return new float[4];
        case ShaderDataType::Mat3:      return new float[9];
        case ShaderDataType::Mat4:      return new float[16];
        case ShaderDataType::Int:       return new int32_t;
        case ShaderDataType::Int2:      return new int32_t[2];
        case ShaderDataType::Int3:      return new int32_t[3];
        case ShaderDataType::Int4:      return new int32_t[4];
        case ShaderDataType::Bool:      return new bool;
        case ShaderDataType::None:
        default:                        return nullptr;
        }
    }
}