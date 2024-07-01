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

// GLM extra constants
namespace glm
{ 
    inline constexpr glm::mat4 m4_identity(1.f);
    
    inline constexpr glm::vec4 v4_zero        (  0.f,  0.f,    0.f,    0.f );
    inline constexpr glm::vec4 v4_one         (  1.f,  1.f,    1.f,    1.f );

    inline constexpr glm::vec4 v4_black       (  0.f,  0.f,    0.f,    1.f );
    inline constexpr glm::vec4 v4_blue        (  0.f,  0.f,    1.f,    1.f );
    inline constexpr glm::vec4 v4_light_blue  (  .3f,  .3f,    1.f,    1.f );
    inline constexpr glm::vec4 v4_cyan        (  0.f,  1.f,    1.f,    1.f );
    inline constexpr glm::vec4 v4_gray        (  .5f,  .5f,    .5f,    1.f );
    inline constexpr glm::vec4 v4_dark_gray   (  .2f,  .2f,    .2f,    1.f );
    inline constexpr glm::vec4 v4_green       (  0.f,  1.f,    0.f,    1.f );
    inline constexpr glm::vec4 v4_light_green (  .3f,  1.f,    .3f,    1.f );
    inline constexpr glm::vec4 v4_grey        (  .5f,  .5f,    .5f,    1.f );
    inline constexpr glm::vec4 v4_dark_grey   (  .2f,  .2f,    .2f,    1.f );
    inline constexpr glm::vec4 v4_magenta     (  1.f,  0.f,    1.f,    1.f );
    inline constexpr glm::vec4 v4_red         (  1.f,  0.f,    0.f,    1.f );
    inline constexpr glm::vec4 v4_light_red   (  1.f,  .3f,    .3f,    1.f );
    inline constexpr glm::vec4 v4_white       (  1.f,  1.f,    1.f,    1.f );
    inline constexpr glm::vec4 v4_white_faded (  1.f,  1.f,    1.f,    0.f );
    inline constexpr glm::vec4 v4_yellow      (  1.f, .92f,  .016f,    1.f );
    inline constexpr glm::vec4 v4_orange      ( .97f, .60f,   .11f,    1.f );

    inline constexpr glm::vec2 v2_zero  ( 0,  0 );
    inline constexpr glm::vec2 v2_one   ( 1,  1 );
    inline constexpr glm::vec2 v2_right ( 1,  0 );
    inline constexpr glm::vec2 v2_left  (-1,  0 );
    inline constexpr glm::vec2 v2_up    ( 0,  1 );
    inline constexpr glm::vec2 v2_down  ( 0, -1 );

    inline constexpr glm::vec3 v3_zero  ( 0,  0,  0 );
    inline constexpr glm::vec3 v3_one   ( 1,  1,  1 );
    inline constexpr glm::vec3 v3_right ( 1,  0,  0 );
    inline constexpr glm::vec3 v3_left  (-1,  0,  0 );
    inline constexpr glm::vec3 v3_up    ( 0,  1,  0 );
    inline constexpr glm::vec3 v3_down  ( 0, -1,  0 );
}

namespace Graphics
{
    enum class BlendingMode
    {
        Alpha,
        Solid,
        Add,
        Multiply
    };

    enum class API
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
        None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Sampler2D, Int2, Int3, Int4, Bool
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
        case ShaderDataType::Sampler2D: return 4 * 32;
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
        case ShaderDataType::Sampler2D: return new int32_t[32];
        case ShaderDataType::Int2:      return new int32_t[2];
        case ShaderDataType::Int3:      return new int32_t[3];
        case ShaderDataType::Int4:      return new int32_t[4];
        case ShaderDataType::Bool:      return new bool;
        case ShaderDataType::None:
        default:                        return nullptr;
        }
    }
}