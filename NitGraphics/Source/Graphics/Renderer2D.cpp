#include "Renderer2D.h"
#include "Graphics.h"
#include "RenderAPI.h"
#include "VertexObject.h"
#include "Texture2D.h"
#include "Shader.h"
#include "Material.h"

namespace Graphics
{
    struct QuadVertex
    {
        glm::vec4 Position = glm::v4_zero;
        glm::vec4 Tint     = glm::v4_white;
        glm::vec2 UV       = glm::v2_zero;
        int32_t   Texture  =  0;
        int32_t   EntityID = -1;
    };

    struct Renderer2DContext
    {
        std::vector<std::shared_ptr<Texture2D>> texturesToBind;
        std::vector<int32_t>                    textureSlots;
        uint32_t                                lastTextureSlot = 1;
        glm::mat4                               projectionView  = glm::m4_identity;
        std::shared_ptr<Material>               material        = nullptr;
        std::shared_ptr<IndexBuffer>            IBO             = nullptr;

        // Quad stuff
        std::shared_ptr<VertexArray>            quadVAO         = nullptr;
        std::shared_ptr<VertexBuffer>           quadVBO         = nullptr;
        QuadVertex*                             quadBatch       = nullptr;
        QuadVertex*                             lastQuadVertex  = nullptr;
        std::shared_ptr<Material>               quadMaterial    = nullptr;
        std::shared_ptr<Texture2D>              whiteTexture    = nullptr;
        uint32_t                                quadCount       = 0;
        uint32_t                                quadIndexCount  = 0;
    };

    constexpr uint32_t g_maxPrimitives       = 1;
    constexpr uint32_t g_verticesPerPrimitve = 4;
    constexpr uint32_t g_indicesPerPrimitive = 6;
    constexpr uint32_t g_maxTextureSlots     = 32;

    constexpr std::array<glm::vec4, 4> g_vertexPositions = {
        glm::vec4(-.5f, -.5f, 0.f, 1.f), // bottom-left
        glm::vec4( .5f, -.5f, 0.f, 1.f), // bottom-right
        glm::vec4( .5f,  .5f, 0.f, 1.f), // top-right
        glm::vec4(-.5f,  .5f, 0.f, 1.f)  // top-left
    };

    constexpr std::array<glm::vec2, 4> g_vertexUVs = {
        glm::vec2(0, 0), // bottom-left
        glm::vec2(1, 0), // bottom-right
        glm::vec2(1, 1), // top-right
        glm::vec2(0, 1)  // top-left
    };

    Renderer2DContext* g_context2D = nullptr;

    void Create2DRenderer(const Render2DInitArgs args)
    {
        assert(!g_context2D);
        g_context2D = new Renderer2DContext();

        g_context2D->quadVAO = VertexArray::Create();

        g_context2D->quadVBO = VertexBuffer::Create(g_verticesPerPrimitve * g_maxPrimitives * sizeof(QuadVertex));
        
        g_context2D->quadVBO->SetLayout({
            { ShaderDataType::Float4, "a_Position" },
            { ShaderDataType::Float4, "a_Tint"     },
            { ShaderDataType::Float2, "a_UV"       },
            { ShaderDataType::Float,  "a_Texture"  },
            { ShaderDataType::Float,  "a_EntityID" }
        });
        
        g_context2D->quadVAO->AddVertexBuffer(g_context2D->quadVBO);
        g_context2D->quadBatch = new QuadVertex[g_maxPrimitives * g_verticesPerPrimitve];

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
            g_context2D->IBO = IndexBuffer::Create(indices, maxIndices);
            delete[] indices;
        }

        g_context2D->quadVAO->SetIndexBuffer(g_context2D->IBO);


        g_context2D->texturesToBind.resize(g_maxTextureSlots);

        g_context2D->whiteTexture = Texture2D::Create();
        constexpr uint32_t whiteTextureData = 0xffffffff;
        g_context2D->whiteTexture->UploadToGPU(&whiteTextureData, 1, 1, 4);
        g_context2D->texturesToBind[0] = g_context2D->whiteTexture;

        g_context2D->textureSlots.resize(g_maxTextureSlots);
        for (uint32_t i = 0; i < g_maxTextureSlots; i++)
            g_context2D->textureSlots[i] = i;

        // Default quad Material
        {
            auto quadShader = Shader::Create();

            const char* vertexShaderSource = R"(
                #version 410 core
        
                layout(location = 0) in vec4 a_Position;
                layout(location = 1) in vec4 a_Tint;
                layout(location = 2) in vec2 a_UV;
                layout(location = 3) in int  a_Texture;
                layout(location = 4) in int  a_EntityID;

                uniform mat4 u_ProjectionView;        
        
                out vec4     v_Tint;
                out vec2     v_UV;
                flat out int v_Texture;
                flat out int v_EntityID;

                void main()
                {
                    gl_Position   = u_ProjectionView * a_Position;
                    v_Tint        = a_Tint;
                    v_UV          = a_UV;
                    v_Texture     = a_Texture;
                    v_EntityID    = a_EntityID;
                }
            )";

            const char* fragmentShaderSource = R"(        
                #version 410 core
        
                layout(location = 0) out vec4 o_Color;
                layout(location = 1) out int  o_EntityID;
        
                uniform sampler2D u_Textures[32];
        
                in vec4      v_Tint;
                in vec2      v_UV;
                flat in int  v_Texture;
                flat in int  v_EntityID;

                void main()
                {
                    o_Color    = texture(u_Textures[v_Texture], v_UV) * v_Tint;
                    o_EntityID = v_EntityID;
                }
            )";

            quadShader->Compile(vertexShaderSource, fragmentShaderSource);
            g_context2D->quadMaterial = std::make_shared<Material>(quadShader);
        }

        g_context2D->lastQuadVertex = g_context2D->quadBatch;
    }

    void StartBatch()
    {
        g_context2D->lastQuadVertex  = g_context2D->quadBatch;
        g_context2D->quadCount       = 0;
        g_context2D->lastTextureSlot = 0;
        g_context2D->quadIndexCount  = 0;
    }

    void Flush()
    {
        for (uint32_t i = 0; i < g_context2D->lastTextureSlot; i++)
            g_context2D->texturesToBind[i]->Bind(i);

        Material* material = g_context2D->material ? g_context2D->material.get() : g_context2D->quadMaterial.get();
        assert(material);

        material->SetConstantSampler2D("u_Textures[0]", &g_context2D->textureSlots.front(), g_maxTextureSlots);
        material->SetConstantMat4("u_ProjectionView", g_context2D->projectionView);
        material->SubmitConstants();
        
        if (const uint32_t vertexDataSize = static_cast<uint32_t>(reinterpret_cast<uint8_t*>(g_context2D->lastQuadVertex) -
            reinterpret_cast<uint8_t*>(g_context2D->quadBatch)))
        {
            g_context2D->quadVBO->SetData(g_context2D->quadBatch, vertexDataSize);
            DrawElements(g_context2D->quadVAO, g_context2D->quadIndexCount);
        }
    }

    void NextBatch()
    {
        Flush();
        StartBatch();
    }

    void BeginRender2D(const glm::mat4& projection /*= glm::m4_identity */, const std::shared_ptr<Material>& material /*= nullptr*/)
    {
        g_context2D->material = material;
        g_context2D->projectionView = projection;
        StartBatch();
    }

    int AssignTextureSlot(const std::shared_ptr<Texture2D>& texture)
    {
        int textureSlot = 0;

        const int lastTextureSlot = g_context2D->lastTextureSlot;

        if (texture)
        {
            // Search existing texture
            for (int32_t i = 1; i < lastTextureSlot; i++)
            {
                if (g_context2D->texturesToBind[i]->GetTextureID() == texture->GetTextureID())
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

                g_context2D->texturesToBind[lastTextureSlot] = texture;
                textureSlot = lastTextureSlot;
                g_context2D->lastTextureSlot++;
            }
        }
        return textureSlot;
    }

    void DrawQuad(const std::shared_ptr<Texture2D>& texture, const glm::mat4& transform /*= glm::m4_identity*/, const glm::vec4& tint /*= glm::v4_white*/)
    {
        if (g_context2D->quadCount >= g_maxPrimitives)
        {
            NextBatch();
        }

        const int textureSlot = AssignTextureSlot(texture);

        for (uint8_t i = 0; i < g_verticesPerPrimitve; ++i)
        {
            QuadVertex& vertex = *g_context2D->lastQuadVertex;

            vertex.Position = transform * g_vertexPositions[i];
            vertex.UV = g_vertexUVs[i];
            vertex.Tint = tint;
            vertex.Texture = AssignTextureSlot(texture);

            g_context2D->lastQuadVertex++;
        }

        g_context2D->quadIndexCount += g_indicesPerPrimitive;
        g_context2D->quadCount++;
    }

    void EndRender2D()
    {
        Flush();
    }

    void Destroy2DRenderer()
    {
        assert(g_context2D && g_context2D->quadBatch);

        delete g_context2D->quadBatch;
        g_context2D->quadBatch = nullptr;

        delete g_context2D;
        g_context2D = nullptr;
    }
}