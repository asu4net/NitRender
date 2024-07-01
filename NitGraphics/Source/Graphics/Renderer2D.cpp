#include "Renderer2D.h"
#include "RenderAPI.h"
#include "VertexObject.h"
#include "Graphics.h"
#include "Texture2D.h"
#include "Shader.h"
#include "Material.h"

namespace Graphics
{
    constexpr uint32_t g_maxPrimitives       = 3000;
    constexpr uint32_t g_verticesPerPrimitve = 4;
    constexpr uint32_t g_indicesPerPrimitive = 6;
    constexpr uint32_t g_maxTextureSlots     = 32;

    constexpr std::array<glm::vec3, 4> g_vertexPositions = {
        glm::vec3(-.5f, -.5f, 0), // bottom-left
        glm::vec3( .5f, -.5f, 0), // bottom-right
        glm::vec3( .5f,  .5f, 0), // top-right
        glm::vec3(-.5f,  .5f, 0)  // top-left
    };
    
    constexpr std::array<glm::vec2, 4> g_vertexUVs = {
        glm::vec2(0, 0), // bottom-left
        glm::vec2(1, 0), // bottom-right
        glm::vec2(1, 1), // top-right
        glm::vec2(0, 1)  // top-left
    };

    struct Renderer2DContext
    {
        std::vector<Texture2DSPtr> texturesToBind;
        std::vector<int32_t>       textureSlots;
        uint32_t                   textureSlot      = 1;
        glm::mat4                  projection   = glm::m4_identity;  
        Material*                  material     = nullptr;
        Texture2DSPtr              whiteTexture     = nullptr;
        IndexBufferSPtr            IBO              = nullptr;
    };

    Renderer2DContext* g_context = nullptr;

    /* QuadBatchPtr<T> batch = std::make_unique<QuadBatch>();
        batch->maxVertices    = g_MaxPrimitives * g_VerticesPerPrimitve;
        batch->maxIndices     = g_MaxPrimitives * g_IndicesPerPrimitive;
        batch->indexCount     = 0;
        batch->vertices       = new T[batch->maxVertices];
        batch->lastVertex     = batch->vertices;
        batch->VAO            = VertexArray::Create();
        batch->VBO            = VertexBuffer::Create(sizeof(T) * g_VerticesPerPrimitve);
        batch->VBO            ->SetLayout(layout);
        batch->VAO            ->SetIndexBuffer(IBO);
        return std::move(batch);
    */

    int GetTextureSlot(const Texture2DSPtr& texture)
    {
        int textureSlot = 0;
        const uint32_t lastTextureSlot = g_context->textureSlot;

        if (texture)
        {
            // Search existing texture
            for (uint32_t i = 1; i < lastTextureSlot; i++)
            {
                if (g_context->texturesToBind[i]->GetTextureID() == texture->GetTextureID())
                {
                    textureSlot = i;
                    break;
                }
            }

            // If not exists save the new texture
            if (textureSlot == 0)
            {
                if (lastTextureSlot > g_maxTextureSlots)
                {
                    NextBatch();
                }

                g_context->texturesToBind[lastTextureSlot] = texture;
                textureSlot = lastTextureSlot;
                g_context->textureSlot++;
            }
        }
        return textureSlot;
    }

    void InitRender2D(const Render2DInitArgs args)
    {
        assert(!g_context);
        g_context = new Renderer2DContext();

        // We create the index buffer shared across all the 2D Primitives
        {
            const uint32_t maxIndices = g_maxPrimitives * g_indicesPerPrimitive;

            uint32_t* indices = new uint32_t[maxIndices];

            uint32_t offset = 0;
            for (uint32_t i = 0; i < maxIndices; i += 6)
            {
                indices[i + 0] = offset + 0;
                indices[i + 1] = offset + 1;
                indices[i + 2] = offset + 2;

                indices[i + 3] = offset + 2;
                indices[i + 4] = offset + 3;
                indices[i + 5] = offset + 0;

                offset += 4;
            }
            g_context->IBO = IndexBuffer::Create(indices, maxIndices);
            delete[] indices;
        }

        g_context->texturesToBind.reserve(g_maxTextureSlots);
        g_context->textureSlots.reserve(g_maxTextureSlots);

        g_context->whiteTexture = Texture2D::Create();
        constexpr uint32_t whiteTextureData = 0xffffffff;
        g_context->whiteTexture->UploadToGPU(&whiteTextureData, 1, 1, 4);
    }
    
    void NextBatch()
    {
        EndRender2D();
        BeginRender2D(g_context->material, g_context->projection);
    }

    void BeginRender2D(Material* material /*= nullptr*/, const glm::mat4& projection /*= glm::m4_identity */)
    {
        g_context->material   = material;
        g_context->projection = projection;
    }
    
    void SubmitSprite(const glm::mat4& trasnform, const Texture2DSPtr& texture /*= nullptr*/, const glm::vec4& tintColor /*= glm::white*/)
    {

    }

    void EndRender2D()
    {
        
    }

    void FinishRender2D()
    {
        assert(g_context);
        delete g_context;
        g_context = nullptr;
    }
}